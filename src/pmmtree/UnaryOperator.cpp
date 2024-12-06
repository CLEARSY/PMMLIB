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
#include <pmmtree/NodeWriter.h>
#include "UnaryOperator.h"

namespace theory
{

UnaryOperator::UnaryOperator(const std::string& val, BNode *child, int type)
: ChildNode(NODE_UNARY_OPERATOR, val, child), operatorType(type)
{
}

UnaryOperator::UnaryOperator(const UnaryOperator& op)
: ChildNode(op), operatorType(op.operatorType)
{

}

UnaryOperator::~UnaryOperator()
{
}

BNode*
UnaryOperator::copy() const
{
	return new UnaryOperator(*this);
}

int
UnaryOperator::getPriority() const
{
	if(getValue() == "-")
	{
		return 210;
	}
//	else if(getValue() == "~")
//	{
//		return 230;
//	}
	else
	{
        return MaxPriority;
	}
}

void
UnaryOperator::writeTo(NodeWriter& n) const
{
        bool add_paren = (getPriority() >= getChild()->getPriority());

	switch(operatorType)
	{
	case CALL:
		n.write(getValue());
		add_paren = true;
		break;
	case PREFIXED:
                n.write(" ");
		n.write(getValue());
		break;
	case PAREN:
		add_paren = false;
		n.write(getValue());
                n.increaseLevel();
		break;
	default:
		break;
	}

	if(add_paren)
	{
		n.write("(");
                n.increaseLevel();
	}
	getChild()->writeTo(n);
	if(add_paren)
	{
            n.decreaseLevel();
            n.write(")");
	}

	switch(operatorType)
	{
	case POSTFIXED:
		n.write(getValue());
		break;
	case PAREN:
                n.decreaseLevel();
		n.write(getClosingValue());
		break;
	default:
		break;
	}
}
};
