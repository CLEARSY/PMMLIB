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
#ifndef PMMFACTORY_H_
#define PMMFACTORY_H_
#include "PmmFile.h"
#include "TheoryNode.h"
#include <pmmtree/TextPos.h>

namespace theory {

class TokenValue
{
public:
        TokenValue()  { }
        TokenValue(const char *c) : value(c) { }

        TokenValue(const TokenValue& v) : value(v.value), pos(v.pos) { }

	TokenValue& operator = (const TokenValue& v)
	{
		value = v.value;
                pos = v.pos;
		return *this;
	}

	std::string value;
        TextPos pos;
};

/**
 * The class that creates the AST elements for the PMM parser
 */
class PmmFactory
{
public:
	PmmFactory();
	virtual ~PmmFactory();

	PmmFile *createPmm();

	TheoryNode *createTheory(const TokenValue& name);

	BNode *createIdent(const TokenValue& name);
	BNode *createString(const TokenValue& value);
	BNode *createInteger(const TokenValue& value);
    BNode *createReal(const TokenValue& value);
	BNode *createEmptySet(const TokenValue& value);
	BNode *createEmptySeq(const TokenValue& value);
	BNode *createParen(const TokenValue& value, BNode *child);

	BNode *createBinaryOperator(const TokenValue& op, BNode *left, BNode *right);
	BNode *createUnaryOperator(const TokenValue& op, BNode *child, bool postfixed);
	BNode *createFctOperator(const TokenValue& op, BNode *child);

	BNode *createRelCall(const TokenValue &v, BNode *rel, BNode *args);
	BNode *createFctCall(const TokenValue &v, BNode *rel, BNode *args);

        BNode *createQuantified(const TokenValue& op, BNode *vars, BNode *formula);


	/**
	 * Creates a "substitution" binary operator. Substitution operators
	 * appears when formulas such as
	 * <pre>
	 * [x:=y]a
	 * </pre>
	 * occurs.
	 * In that case, a substitution operator is created with
	 * left child <pre>[x:=y]</pre> and right chid <pre>a</pre>.
	 * Although there are no "real" token to provide, a TokenValue
	 * parameter is still required. The value of the token will
	 * not be used, however, its line and column information will
	 * be used to assign a position to this operator.
	 *
	 * @param t a TokenValue used to provide line and column information
	 * @param subst the left part of the substitution
	 * @param formula the formula that is substitued
	 */
	BNode *createSubstitution(const TokenValue& t, BNode *subst, BNode *formula);

};

};

#endif /*PMMFACTORY_H_*/
