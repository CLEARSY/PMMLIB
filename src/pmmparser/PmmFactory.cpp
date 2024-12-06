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
#include "PmmFactory.h"
#include <pmmtree/Joker.h>
#include <pmmtree/LeafNode.h>
#include <pmmtree/UnaryOperator.h>
#include <pmmtree/BinaryOperator.h>

namespace theory {

PmmFactory::PmmFactory()
{
}

PmmFactory::~PmmFactory()
{
}

PmmFile*
PmmFactory::createPmm()
{
	return new PmmFile;
}

TheoryNode*
PmmFactory::createTheory(const TokenValue& v)
{
	TheoryNode *result = new TheoryNode(v.value);
        result->setPosition(v.pos);
	return result;
}

BNode*
PmmFactory::createIdent(const TokenValue& v)
{
	std::string value = v.value;
	BNode *result;
	if(value.length() == 1)
	{
		result = new Joker(value);
	}
	else
	{
		result = new LeafNode(NODE_IDENT, value);
	}
        result->setPosition(v.pos);
	return result;
}

BNode*
PmmFactory::createBinaryOperator(const TokenValue& op, BNode *left, BNode *right)
{
	BNode *result = new BinaryOperator(op.value, left, right);
        result->setPosition(op.pos);
	return result;
}

BNode*
PmmFactory::createUnaryOperator(const TokenValue& op, BNode *child, bool postfixed)
{
	int op_type = postfixed ? UnaryOperator::POSTFIXED : UnaryOperator::PREFIXED;
	BNode *result = new UnaryOperator(op.value, child, op_type);
        result->setPosition(op.pos);

	return result;
}

BNode*
PmmFactory::createFctOperator(const TokenValue& op, BNode *child)
{
	BNode *result = new UnaryOperator(op.value, child, UnaryOperator::CALL);
        result->setPosition(op.pos);

	return result;
}

BNode*
PmmFactory::createInteger(const TokenValue& v)
{
	BNode *result = new LeafNode(NODE_INTEGER_LITERAL, v.value);
        result->setPosition(v.pos);
	return result;
}

BNode*
PmmFactory::createReal(const TokenValue& v)
{
    BNode *result = new LeafNode(NODE_REAL_LITERAL, v.value);
        result->setPosition(v.pos);
    return result;
}

BNode*
PmmFactory::createString(const TokenValue& v)
{
	BNode *result = new LeafNode(NODE_STRING_LITERAL, v.value);
        result->setPosition(v.pos);
	return result;
}

BNode*
PmmFactory::createParen(const TokenValue& v, BNode *child)
{
        BNode *result = new UnaryOperator(v.value, child, UnaryOperator::PAREN);
        result->setPosition(v.pos);
        return result;
}

BNode*
PmmFactory::createRelCall(const TokenValue& v, BNode *rel, BNode *args)
{
	BNode *result = createBinaryOperator(v, rel, args);
        result->setPosition(v.pos);
	return result;
}

BNode*
PmmFactory::createFctCall(const TokenValue& v, BNode *f, BNode *args)
{
	BNode *result = createBinaryOperator(v, f, args);
        result->setPosition(v.pos);
	return result;
}

BNode *
PmmFactory::createQuantified(const TokenValue& op, BNode *vars, BNode *formula)
{
	return createBinaryOperator(op, vars, formula);
}

BNode *
PmmFactory::createEmptySet(const TokenValue& v)
{
	BNode *result = new LeafNode(NODE_OTHER, "{}");
        result->setPosition(v.pos);
	return result;
}

BNode *
PmmFactory::createEmptySeq(const TokenValue& v)
{
	BNode *result = new LeafNode(NODE_OTHER, "[]");
        result->setPosition(v.pos);
	return result;
}

BNode*
PmmFactory::createSubstitution(const TokenValue& v, BNode *subst, BNode *formula)
{
	TokenValue tmp = v;
	tmp.value = "[]";
	return createBinaryOperator(tmp, subst, formula);
}
}; // namespace theory
