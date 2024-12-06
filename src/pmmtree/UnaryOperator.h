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
#ifndef UNARYOPERATOR_H_
#define UNARYOPERATOR_H_

#include "ChildNode.h"
namespace theory
{
class UnaryOperator : public ChildNode
{
public:
	typedef enum UnaryOperatorType {
		POSTFIXED, // postfixed operator
		PREFIXED,  // prefixed operator
		PAREN,     // paren operator
		CALL       // operator with function call syntax (bool, not)
	} UnaryOperatorType;

	UnaryOperator(const std::string& val, BNode *child, int type);
	UnaryOperator(const UnaryOperator&);
	virtual ~UnaryOperator();

	BNode *copy() const;

	virtual int getPriority() const;

	void writeTo(NodeWriter& n) const;
        int getOperatorType() const { return operatorType; }

private:
	int operatorType;
};
};

#endif /*UNARYOPERATOR_H_*/
