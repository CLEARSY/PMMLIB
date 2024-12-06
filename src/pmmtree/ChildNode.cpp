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
#include "ChildNode.h"

namespace theory
{
ChildNode::ChildNode(int type, const std::string& val, BNode *c)
: BNode(type, val), child(c)
{
}

ChildNode::ChildNode(const ChildNode& n)
: BNode(n), child(0)
{
	if(n.getChild())
	{
		const BNode *src = n.getChild();
		BNode *current = src->copy();
		setChild(current);

		src = src->getSibling();
		while(src)
		{
			current->setSibling(src->copy());
			current = current->getSibling();

			src = src->getSibling();
		}
	}
}

ChildNode::~ChildNode()
{
    freeChildren();
}

BNode*
ChildNode::setChild(BNode *new_child)
{
    /*
      todo: comprendre pour quelle raison la ligne suivante corrompt
      la representation de termes, et essayer de faire une gestion
      memoire 'propre'. 
      freeChildren(); <-- la ligne en cause
    */
	child = new_child;
	return new_child;
}

void
ChildNode::freeChildren() {
    // delete all the children nodes
    BNode *current = child;
    while(current)
    {
        BNode *to_delete= current;
        current = current->getSibling();
        delete to_delete;
    }
    child = NULL;
}

std::string
ChildNode::getClosingValue() const
{
	switch(getValue()[0])
	{
	case '(':
		return ")";
	case '[':
		return "]";
	case '{':
		return "}";
	default:
		return "";
	}
}

};
