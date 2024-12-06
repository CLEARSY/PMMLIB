#include<cassert>

#include "Jokerizer.h"

#include "BinaryOperator.h"
#include "BNode.h"
#include "ChildNode.h"
#include "Joker.h"
#include "UnaryOperator.h"

namespace theory {

static bool shouldJokerize(const BNode *source);

Jokerizer::Jokerizer(int depth, bool keepInt)
    : depth(depth),
      keepInt(keepInt),
      next_joker('a'),
      binding()
{}

Jokerizer::~Jokerizer()
{
    for(auto p: binding)
	delete p.first;
}

bool Jokerizer::available() const {
    return ('A' <= next_joker && next_joker <= 'Z') ||
	('a' <= next_joker && next_joker <= 'z');
}

char Jokerizer::nextJoker() const {
    return next_joker;
}

void Jokerizer::consumeJoker() {
    /* note: 'A' < 'Z' < 'a' < 'z' according to encoding
       but Jokerizer uses lowercase before uppercase. */
    if(next_joker == 'z')
	next_joker = 'A';
    else
	next_joker += 1;
}

void Jokerizer::cancelBinding(const BNode* value) {
    int i = binding.size() - 1;
    while(0 <= i) {
	if (binding.at(i).second == value) {
	    binding.at(i).second = NULL;
	    break;
	}
	i -= 1;
    }
    assert(0 <= i);
}

BNode* Jokerizer::createBinding(BNode* value) {
    if(!available())
	return NULL;
    BNode* result = new Joker(next_joker);
    consumeJoker();
    binding.push_back(std::make_pair(result, value));
    return result->copy();
}

BNode* Jokerizer::lookupBinding(BNode* value) {
    int i = binding.size() - 1;
    while(0 <= i) {
	if (binding.at(i).second != NULL &&
	    binding.at(i).second->compare(value))
	    return binding.at(i).first;
	i -= 1;
    }
    return NULL;
}

BNode* Jokerizer::handle(BNode* src) {
    std::vector< const BNode* > bound;
    return handle_rec(src, depth, bound);
}

static void
pushQuantifiedVariables(std::vector<const BNode* >& vec, const BNode* qvar) {
    const BinaryOperator* bin = dynamic_cast< const BinaryOperator* >(qvar);
    if(bin) {
	const BNode* l = qvar->getChild();
	const BNode* r = l->getSibling();
	pushQuantifiedVariables(vec, l);
	pushQuantifiedVariables(vec, r);
    } else
	vec.push_back(qvar);
}

BNode* Jokerizer::handle_rec
(BNode* src, int level, std::vector< const BNode* >& bound)
{
    /* interpreted constants are not jokerized */
    if(src->getType() == NODE_IDENT
       && (src->getValue() == "TRUE" || src->getValue() == "FALSE"))
        return src->copy();
    if(keepInt
       && (src->getType() == NODE_INTEGER_LITERAL || src->getType() == NODE_REAL_LITERAL
	   || (src->getType() == NODE_IDENT && src->getValue() == "NATURAL")))
        return src->copy();


    if ((level == 0 && !src->find(bound)) || shouldJokerize(src)) {
	BNode* joker = lookupBinding(src);
	if(joker != NULL)
	    return joker->copy();
	else
	    return createBinding(src);
    }
    size_t init_sz = bound.size();
    {
        const BinaryOperator* bin(dynamic_cast< const BinaryOperator* >(src));
        if (bin && (bin->getOperatorType() & BinaryOperator::QUANTIFIED))
	    pushQuantifiedVariables(bound, bin->getChild());
    }

    BNode *res_child = NULL;
    BNode *cur_child = NULL;
    BNode *src_child = src->getChild();
    if(0 < level)
	level -= 1;
    while (src_child) {
        BNode *child = handle_rec(src_child, level, bound);
        if (child == NULL)
            return NULL;
        if (res_child == NULL)
            res_child = child;
        else
            cur_child->setSibling(child);
        cur_child = child;
        src_child = src_child->getSibling();
    }
    BNode* res;
    /* avoids full copy of src */
    UnaryOperator* tmp1 = dynamic_cast<UnaryOperator*>(src);
    if(tmp1 != NULL)
	res = new UnaryOperator(src->getValue(), res_child, tmp1->getOperatorType());
    else {
	BinaryOperator* tmp2 = dynamic_cast<BinaryOperator*>(src);
	assert(tmp2 != NULL);
	assert(res_child->getSibling() != NULL);
	res = new BinaryOperator(src->getValue(), res_child,
				 res_child->getSibling());
    }
    while(init_sz < bound.size()) {
	cancelBinding(bound.back());
        bound.pop_back();
    }
    return res;
}


static bool shouldJokerize(const BNode *source)
{
    return source &&
            (dynamic_cast<const LeafNode*>(source) ||
             (source->getType() == NODE_BINARY_OPERATOR &&
	     source->getValue() == "$"));
}


};
