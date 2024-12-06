/******************************* CLEARSY **************************************
This file is part of PMMLIB
    Copyright  © CLEARSY 2008-2020 (contact@clearsy.com)

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
#ifndef THEORYNODE_H_
#define THEORYNODE_H_
#include <pmmtree/ChildNode.h>

namespace theory
{
/**
 * Node representing theories
 */
class TheoryNode : public ChildNode
{
public:
	TheoryNode(const std::string&name);
	TheoryNode(const TheoryNode& node);
	virtual ~TheoryNode();

	BNode *copy() const;

	static int type();

	virtual void writeTo(NodeWriter& n) const;

	const TextPos &getTheoryTokenPos() const { return theoryTokenPos; }
	void setTheoryTokenPos(const TextPos &newValue) { theoryTokenPos = newValue; }

	const TextPos &getEndTokenPos() const { return endTokenPos; }
	void setEndTokenPos(const TextPos &newValue) { endTokenPos = newValue; }

	const TextPos &getAndTokenPos() const { return andTokenPos; }
	void setAndTokenPos(const TextPos &newValue) { andTokenPos = newValue; }

private:
	static int nodeType;
	TextPos theoryTokenPos;
	TextPos endTokenPos;
	TextPos andTokenPos;
};

};

#endif /*THEORYNODE_H_*/
