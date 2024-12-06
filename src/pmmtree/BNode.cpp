/******************************* CLEARSY **************************************
This file is part of BPARSERS
    Copyright (C) 2008 ClearSy (contact@clearsy.com)

    BPARSERS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; GNU General Public License version 3
    of the License

    BPARSERS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BPARSERS; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/
#include <common.h>
#include <pmmtree/StreamWriter.h>
#include "BNode.h"
#include "Joker.h"
#include "NodeAttribute.h"
#include "ParenthesisAttribute.h"

namespace theory
{
int
BNode::nextFreeType = NODE_FREE;

BNode::BNode(int t)
: type(t), sibling(0), attributes(0)
{
}

BNode::BNode(int t, const std::string& v)
: type(t), sibling(0), value(v), attributes(0)
{
}

BNode::BNode(const BNode& b)
: type(b.type), sibling(0), value(b.value), attributes(0)
{
}

BNode::~BNode()
{
    NodeAttribute *current = attributes;
    while(current)
    {
        NodeAttribute *next = current->getNext();
        delete current;
        current = next;
    }
}

BNode*
BNode::setChild(BNode *new_child)
{
	std::cerr << "**warning: setting child of non-child node" << std::endl;
	return 0;
}

BNode*
BNode::setSibling(BNode *new_sibling)
{
	sibling = new_sibling;
	return new_sibling;
}

int
BNode::getNewType()
{
	return nextFreeType++;
}

const BNode *
BNode::getChild() const
{
	return 0;
}

BNode *
BNode::getChild()
{
	return 0;
}

bool
BNode::compareNode(const BNode *other) const
{
	return getType() == other->getType() &&
		getValue() == other->getValue();
}


bool
BNode::compare(const BNode *other) const
{
	if(other == this)
	{
		return true;
	}

	if(other)
	{
		if(compareNode(other))
		{
			const BNode *child = getChild();
			const BNode *other_child = other->getChild();

			while(child && other_child)
			{
				if(child->compare(other_child))
				{
					child = child->getSibling();
					other_child = other_child->getSibling();
				}
				else
				{
					return false;
				}
			}
			// at least one of child and
			return child == other_child;
		}
	}

	return false;
}

int
BNode::occurence(const BNode *other) const {
	if (compare(other)) {
		return 1;
	}
	else {
		const BNode *child = getChild();
		int result = 0;
		while(child)
		{
			result += child->occurence(other);
			child = child->getSibling();
		}
		return result;
	}
}

bool
BNode::find(const std::vector< const BNode* >& others) const {
    for (int i = 0; i < others.size(); ++i) {
        if(compare(others.at(i)))
            return true;
    }
    for (const BNode *n = getChild(); n != NULL; n = n->getSibling()) {
        if(n->find(others))
            return true;
    }
    return false;
}

int
BNode::depth() const {
    const BNode* child = getChild();
    int max = -1;
    while (child) {
        int d = child->depth();
        if (d > max)
            max = d;
        child = child->getSibling();
    }
    return max+1;
}

std::ostream& operator << (std::ostream& o, const theory::BNode&b)
{
    theory::StreamWriter w(&o);
    b.writeTo(w);

    return o;
}

int
BNode::getPriority() const
{
    return MaxPriority;
}

NodeAttribute* BNode::getAttribute(const std::string& attribute_name) const
{
    NodeAttribute *current = attributes;

    while(current)
    {
        if(current->getName() == attribute_name)
        {
            return current;
        }
        current = current->getNext();
    }

    return 0;
}

void BNode::setAttribute(NodeAttribute *attr)
{
    if(attr)
    {
        removeAttribute(attr->getName());
    }
    addAttribute(attr);
}

void BNode::addAttribute(NodeAttribute *attr)
{
    attr->setNext(attributes);
    attributes = attr;
}

void BNode::removeAttribute(const std::string& attribute_name)
{
    NodeAttribute *previous = 0;
    NodeAttribute *current = attributes;

    while(current)
    {
        if(current->getName() == attribute_name)
        {
            NodeAttribute *nxt = current->getNext();

            if(previous)
            {
                previous->setNext(nxt);
            }
            else
            {
                attributes = nxt;
            }

            delete current;

            current = nxt;
        }
        else
        {
            previous = current;
            current = current->getNext();
        }
    }
}

BNode* BNode::instanciatedCopy(const JokerInstanciation*j) const
{
    return copy();
}

void BNode::getTokenRange(TextPos& start, TextPos& end)
{
    start.setPos(pos.getLine(), pos.getColumn());
    end.setPos(pos.getLine(), pos.getColumn() + value.size());
}

void BNode::getRange(TextPos& start, TextPos& end)
{
    ParenthesisAttribute *attr = (ParenthesisAttribute*)getAttribute(ParenthesisAttribute::getAttributeName());
    if(attr)
    {
        // If there is a parenthesis attribute, we know that the whole subtree is
        // located within the parenthesis
        start = attr->getOpeningPos();
        end = attr->getClosingPos();
        // Increases the column to point past the closing parenthesis
        ++end;
    }
    else
    {
        getTokenRange(start, end);

        theory::BNode *childs = getChild();
        while(childs)
        {
            childs->mergeRange(start, end);
            childs = childs->getSibling();
        }
    }
}

void BNode::mergeRange(TextPos& start, TextPos& end)
{
    TextPos node_start, node_end;
    getRange(node_start, node_end);
    if(node_start < start)
    {
        start = node_start;
    }

    if(end < node_end)
    {
        end = node_end;
    }

}
};

