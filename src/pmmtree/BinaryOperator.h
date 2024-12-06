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
#ifndef BINARYOPERATOR_H_
#define BINARYOPERATOR_H_
#include <map>
#include <string>

#include "ChildNode.h"
namespace theory
{
class BinaryOperator : public ChildNode
{
public:
    BinaryOperator(const std::string& val, BNode *left, BNode *right, int type);
    BinaryOperator(const std::string& val, BNode *left, BNode *right);
    BinaryOperator(const BinaryOperator&);

	BNode *copy() const;

	void writeTo(NodeWriter& n) const;

	typedef enum OperatorType
	{
		/// default operator type: displayed as left op right
		DEFAULT = 0,
		/// image: either '(' or '['. displayed as left(right) or left[right]
		IMG = 1,
		/// quantified. Displayed as op left . (right)
		QUANTIFIED = 2,
		/// parenthezed quantified. Displayed as op (left) . (right)
		PARENTHEZED_QUANTIFIED = 3,
		/// non-displayed: the operator is not displayed
		NON_DISPLAYED = 4,
		/// mask used to get type type part of the operatorType field
		TYPE_MASK = 7,

		// flags
		SPACE_BEFORE = 8,
        SPACE_AFTER = 16,

        CR_BEFORE = 32,
        CR_AFTER  = 64,
        // Indicates that the cariage returns should be added only for the
        // toplevel operators (i.e. indent > 0)
        CR_AFTER_TOPLEVEL = 128
	} OperatorType;

	virtual int getPriority() const;
    int getOperatorType() const { return operatorType & TYPE_MASK; }

private:
        /*!
         * Indicates whether the node is an "unnormalized" SET. I.e. it is a
         * SET operator that was wrriten as { x | P } within the original
         * file.
         */
        bool isUnnormalisedSet() const;

	/* Writes the given node to the writer, adding parenthesis
	 * around the node if needed
	 * @param node the node that should be written
	 * @param writer the node writer
	 * @param parenthesis indicates whether parenthesis should be added
	 */
	void writeNode(const BNode *node, NodeWriter& writer, bool parenthesis) const;

	typedef std::map<std::string, int> PriorityTable;
	static PriorityTable *priorities;

	int operatorType;

};
};
#endif /*BINARYOPERATOR_H_*/
