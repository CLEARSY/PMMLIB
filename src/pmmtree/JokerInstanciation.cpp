/******************************* CLEARSY **************************************
This file is part of PMMLIB
    Copyright © CLEARSY 2008-2020 (contact@clearsy.com)

    PMMLIB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; GNU General Public License version 3
    of the License

    PMMLIB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PMMLIB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/
#include <common.h>
#include <cassert>
#include <cstring>
#include <pmmtree/Error.h>
#include <pmmtree/NodeWriter.h>
#include <pmmtree/StreamWriter.h>
#include <pmmparser/PmmParser.h>
#include "BNode.h"
#include "Joker.h"
#include "JokerInstanciation.h"
#include "DefaultErrorHandler.h"
#include "BinaryOperator.h"


namespace theory
{
JokerInstanciation::JokerInstanciation()
    : instantiation(INSTANTIATION_COUNT, static_cast<const BNode*>(NULL)),
      level(INSTANTIATION_COUNT, -1),
      history(),
      currentId(0)
{
}

JokerInstanciation::~JokerInstanciation()
{
    while (!history.empty()) {
        delete history.top().first;
        history.pop();
    }
    for (int i=0;i<instantiation.size();i++) {
        if (instantiation.at(i))
            delete instantiation.at(i);
    }
}

int JokerInstanciation::getIndex(char c)
{
    if('a' <= c && c <= 'z')
		return c - 'a';
    if('A' <= c && c <= 'Z')
		return c - 'A' + 26;

	std::string message("Invalid joker: ");
	message += c;

	throw Error(message);
}

char JokerInstanciation::getCharFromIndex(int index)
{
	if(index < 26)
		return 'a' + index;
    return 'A' + index - 26;
}

void JokerInstanciation::push() {
    history.push(std::make_pair(new std::vector< char >(), currentId));
}

void JokerInstanciation::pop() {
    assert(!history.empty());
    std::vector< char >* jokers = history.top().first;
    currentId = history.top().second;
    while (!jokers->empty()) {
        int i = getIndex(jokers->back());
        if (instantiation.at(i))
            delete instantiation.at(i);
        instantiation.at(i) = NULL;
        level.at(i) = -1;
        jokers->pop_back();
    }
    delete jokers;
    history.pop();
}

bool JokerInstanciation::isInstanciated(char joker_id) const
{
    return joker_id != '_' && instantiation.at(getIndex(joker_id)) != NULL;
}

bool JokerInstanciation::hasInstanciation(const BNode *value, char* joker_id) const {
    for (int i=0; i < instantiation.size(); ++i) {
        if (instantiation.at(i) != NULL && instantiation.at(i)->compare(value)) {
            *joker_id = getCharFromIndex(i);
			return true;
		}
	}
	return false;
}

const BNode *JokerInstanciation::getInstanciation(char joker_id) const
{
    return joker_id == '_' ? NULL : instantiation.at(getIndex(joker_id));
}

void JokerInstanciation::restoreToCounter(int old_id) {
    if(old_id > currentId)
        throw Error("JokerInstanciation::restoreToCounter: old_id > currentId");
    if(old_id == currentId)
        return;
    for (int i=0; i < instantiation.size(); ++i) {
        if(level.at(i) > old_id) {
            if (instantiation.at(i))
            delete(instantiation.at(i));
            instantiation.at(i) = NULL;
            level.at(i) = -1;
        }
    }
    currentId = old_id;
}

void JokerInstanciation::reset() {
    for (int i=0; i < instantiation.size(); ++i) {
        if (instantiation.at(i))
        delete(instantiation.at(i));
        instantiation.at(i) = NULL;
        level.at(i) = -1;
    }
    currentId = 0;
}



void JokerInstanciation::setInstanciation(char joker_id , const BNode *value) {
	if(value == NULL) {
          std::string message{"Null value assigned to joker @"};
          message += joker_id;
          throw Error(message);
	}

    if(joker_id != '_') {
        ++currentId;
        int index = getIndex(joker_id);
        instantiation.at(index) = value->copy();
        level.at(index) = currentId;
	}

}

void JokerInstanciation::writeContent(NodeWriter &w)
{
	bool first = true;

	w.write("{ ");

    for(int i=0; i < instantiation.size(); ++i)
	{
        const BNode * value = instantiation.at(i);
        if(value != NULL) {
			if(first)
				first = false;
			else
				w.write(", ");
			std::string tmp;
            tmp.push_back(getCharFromIndex(i));
			w.write(tmp);
			w.write(" |-> ");
			value->writeTo(w);
		}
	}

	w.write(" }");


}

int
JokerInstanciation::internalMatch(const BNode *pattern, const BNode *term, std::vector< char >& jokers)
{
    if(pattern == term)
        return 1;

    if(pattern == NULL)
        return -1;

    if(pattern->getType() == NODE_JOKER)
    {
        // current pattern is a joker
        const Joker *joker = (const Joker*)pattern;
        char c = joker->getJokerChar();

        if(isInstanciated(c)) {
            return getInstanciation(c)->compare(term) ? 1 : -1;
        } else {
            assert(!history.empty());
            history.top().first->push_back(c);
            setInstanciation(c, term);
            return 1;
        }
    }

    if(pattern->compareNode(term))
    {
        const BNode *pattern_child = pattern->getChild();
        const BNode *nodes_child = term->getChild();
        int depth = 0;
        while(pattern_child && nodes_child)
        {
            int m = internalMatch(pattern_child, nodes_child, jokers);
            if (m == -1)
                return -1;
            pattern_child = pattern_child->getSibling();
            nodes_child = nodes_child->getSibling();
            if (depth < m)
                depth = m;
        }
        if (pattern_child == nodes_child)
            return depth+1;
        else
            return -1;
    }

    return -1;
}


int
JokerInstanciation::match(const BNode *pattern, const BNode *term)
{
    static std::vector< char > jokers; // for backtracking
    assert(jokers.empty());

    push();
    int m = internalMatch(pattern, term, jokers);
    // match is successful, return depth (positive)
	if(0 <= m)
		return m;

    pop();
    return -1;
}

int
JokerInstanciation::match(const std::string& pattern, const BNode *source)
{
    DefaultErrorHandler handler(false, false);
    BNode *formula = PmmParser::parseFormula(pattern, handler);
    if (formula == NULL)
        return false;

    int res = match(formula, source);
    delete formula;
    return res;
}

BNode*
JokerInstanciation::jokerize_joker(char* j) {
    if (*j == 'Z')
        return NULL;
    if (*j == 'z')
		*j = 'A';
	else
		*j = (*j)+1;
	std::string joker = "";
	joker += (*j);
	return new Joker(joker);
}

bool
JokerInstanciation::jokerize_allChildsWithSameOccurence(const BNode *source, const BNode *current, int occ) {
	bool all_childs_with_same_occurence = true;
	const BNode *nodes_child = current->getChild();
	while (nodes_child && all_childs_with_same_occurence) {
		all_childs_with_same_occurence = (occ == source->occurence(nodes_child) &&
				jokerize_allChildsWithSameOccurence(source, nodes_child, occ));
		nodes_child = nodes_child->getSibling();
	}
	return all_childs_with_same_occurence;
}

BNode*
JokerInstanciation::jokerize_algo2(const BNode *source, const BNode *current, char* j) {
	char k;
	if (hasInstanciation(current, &k)) {
		std::string joker = "";
		joker += k;
		return new Joker(joker);
	}
	int nb_occ = source->occurence(current);
	bool jokerize = (nb_occ > 1);
	if (jokerize) {
		jokerize = jokerize_allChildsWithSameOccurence(source, current, nb_occ);
	}
    if (jokerize || should_jokerize(current)) {
		BNode* jok = jokerize_joker(j);
		setInstanciation(*j,current);
		return jok;
    } else {
		BNode *res_child = NULL;
		BNode *cur_child = NULL;
		const BNode *nodes_child = current->getChild();
		while (nodes_child) {
			BNode *child = jokerize_algo2(source, nodes_child, j);
			if (child == NULL)
				return NULL;
			if (res_child == NULL)
				res_child = child;
			else
				cur_child->setSibling(child);
			cur_child = child;
			nodes_child = nodes_child->getSibling();
		}
		BNode* res = current->copy();
		res->setChild(res_child);
		return res;
	}
}

bool JokerInstanciation::should_jokerize(const BNode *source)
{
    return source &&
            (dynamic_cast<const LeafNode*>(source) ||
             source->getType() == NODE_BINARY_OPERATOR && source->getValue() == "$");
}

bool JokerInstanciation::has_joker(const BNode *source) {
    if (source == NULL)
        return false;
    if (dynamic_cast<const Joker*> (source))
        return true;
    for (const BNode *n = source->getChild(); n != NULL; n = n->getSibling()) {
        if (has_joker(n))
            return true;
    }
    return false;
}

bool JokerInstanciation::find(const BNode *source, std::vector< const BNode* >& nodes) {
    if (source == NULL)
        return false;
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes.at(i)->compare(source))
            return true;
    }
    for (const BNode *n = source->getChild(); n != NULL; n = n->getSibling()) {
        if (find(n, nodes))
            return true;
    }
    return false;
}

BNode*
JokerInstanciation::jokerize_algo1(const BNode *source, int level, char* j, bool keepLiteralInt) {
    if (dynamic_cast<const Joker*>(source))
        return source->copy();
    if ((keepLiteralInt
         && (source->getType() == NODE_INTEGER_LITERAL
             || (source->getType() == NODE_IDENT && source->getValue() == "NATURAL")))
            || (source->getType() == NODE_IDENT
                && (source->getValue() == "TRUE"
                    || source->getValue() == "FALSE")))
        return source->copy();

    if (has_joker(source)) {
        level++;
    } else if (level == 0 || should_jokerize(source)) {
        char k;
        if (hasInstanciation(source, &k)) {
            std::string joker = "";
            joker += k;
            return new Joker(joker);
        } else {
            BNode* jok = jokerize_joker(j);
            setInstanciation(*j,source);
            return jok;
        }
    }

    BNode *res_child = NULL;
    BNode *cur_child = NULL;
    const BNode *nodes_child = source->getChild();
    while (nodes_child) {
        BNode *child = jokerize_algo1(nodes_child, level-1, j, keepLiteralInt);
        if (child == NULL)
            return NULL;
        if (res_child == NULL)
            res_child = child;
        else
            cur_child->setSibling(child);
        cur_child = child;
        nodes_child = nodes_child->getSibling();
    }
    BNode* res = source->copy();
    res->setChild(res_child);
    return res;
}

BNode*
JokerInstanciation::jokerize_algo3(const BNode *source, int level, char* j, bool keepLiteralInt, std::vector< const BNode* >& bound) {
    if (dynamic_cast<const Joker*>(source))
        return source->copy();
    if ((keepLiteralInt
         && (source->getType() == NODE_INTEGER_LITERAL
             || (source->getType() == NODE_IDENT && source->getValue() == "NATURAL")))
            || (source->getType() == NODE_IDENT
                && (source->getValue() == "TRUE"
                    || source->getValue() == "FALSE")))
        return source->copy();

    if (level == 0 && !find(source, bound) || should_jokerize(source)) {
        char k;
        if (hasInstanciation(source, &k)) {
            std::string joker = "";
            joker += k;
            return new Joker(joker);
        } else {
            BNode* jok = jokerize_joker(j);
            setInstanciation(*j,source);
            return jok;
        }
    }
    if (level > 0)
        level -= 1;
    unsigned count = 0;
    {
        const BinaryOperator* bin = dynamic_cast< const BinaryOperator* >(source);
        if (bin && (bin->getOperatorType() & BinaryOperator::QUANTIFIED)) {
            for(const BNode* var = bin->getChild(); var; var = var->getSibling()) {
                bound.push_back(var);
                count += 1;
            }
        }
    }

    BNode *res_child = NULL;
    BNode *cur_child = NULL;
    const BNode *nodes_child = source->getChild();
    while (nodes_child) {
        BNode *child = jokerize_algo3(nodes_child, level, j, keepLiteralInt, bound);
        if (child == NULL)
            return NULL;
        if (res_child == NULL)
            res_child = child;
        else
            cur_child->setSibling(child);
        cur_child = child;
        nodes_child = nodes_child->getSibling();
    }
    BNode* res = source->copy();
    res->setChild(res_child);
    while(count) {
        bound.pop_back();
        count -= 1;
    }
    return res;
}

BNode*
JokerInstanciation::jokerize(const BNode *source, int level) {
    char j = 'a'-1;
    if (level == -1) {
        return jokerize_algo2(source, source, &j);
    }
    if (level == 0) {
        return jokerize_algo1(source, INSTANTIATION_COUNT, &j);
    }
    else {
        return jokerize_algo1(source, level, &j);
    }
}

BNode*
JokerInstanciation::jokerize_from(const BNode *source, int level, char *j, bool keepLiteralInt) {
    BNode* res = applyInstanciation(source);
    return jokerize_algo1(res, level, j, keepLiteralInt);
}

/**
 * @todo perform applyInstanciation and jokerize_algo3 in a single pass, avoiding the construction
 * and destruction of a temporary term
 * @todo move bound and keepLiteralInt variables in JokerInstanciation objects?
 */
BNode*
JokerInstanciation::jokerize_from2(const BNode *source, int level, char *j, bool keepLiteralInt) {

    static std::vector< const BNode *> bound; // accumulates bound variables in recursive calls of jokerize_algo3

    assert(bound.empty());

    BNode* tmp = applyInstanciation(source);
    BNode* res = jokerize_algo3(tmp, level, j, keepLiteralInt, bound);

    assert(bound.empty()); // jokerize_algo3 should pop all it pushes to bound
    delete tmp;

    return res;
}

BNode*
JokerInstanciation::applyInstanciation(const BNode *source) {
	char k;
	if (hasInstanciation(source, &k)) {
		std::string joker = "";
		joker += k;
		return new Joker(joker);
	}
    else if (should_jokerize(source)) {
		return source->copy();
	}
	else {
		BNode *res_child = NULL;
		BNode *cur_child = NULL;
		const BNode *nodes_child = source->getChild();
		while (nodes_child) {
			BNode *child = applyInstanciation(nodes_child);
			if (child == NULL)
				return NULL;
			if (res_child == NULL)
				res_child = child;
			else
				cur_child->setSibling(child);
			cur_child = child;
			nodes_child = nodes_child->getSibling();
		}
		BNode* res = source->copy();
		res->setChild(res_child);
		return res;
	}
}

int
JokerInstanciation::matchSubExpression(const BNode *pattern, const BNode *nodes)
{
	int m = match(pattern, nodes);
	if(0 <= m)
	{
		return m;
	}
	const BNode *current = nodes->getChild();
	while(current)
	{
		int mc = matchSubExpression(pattern, current);
		if(0<=mc)
		{
			return mc;
		}
		current = current->getSibling();
	}

	return -1;
}

std::ostream& operator<< (std::ostream& o, const theory::JokerInstanciation& j)
{
	bool first = true;

	o << "{ ";
    for(int i=0; i<theory::JokerInstanciation::INSTANTIATION_COUNT; ++i)
	{
        const theory::BNode * value = j.instantiation.at(i);
		if(value != NULL)
		{
			if(first)
			{
				first = false;
			}
			else
			{
				o << ", ";
			}
			o << "@"
			<< theory::JokerInstanciation::getCharFromIndex(i)
			<< " |-> "
			<< *value;
		}
	}

	o << " }";

	return o;
}
}
