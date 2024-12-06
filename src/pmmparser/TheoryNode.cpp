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
#include <common.h>
#include <pmmtree/NodeWriter.h>
#include "TheoryNode.h"

namespace theory
{
int
TheoryNode::nodeType = -1;

TheoryNode::TheoryNode(const std::string& name)
: ChildNode(type(), name),
  theoryTokenPos(0, 0),
  endTokenPos(0, 0),
  andTokenPos(0, 0)
{
}

TheoryNode::TheoryNode(const TheoryNode& t)
: ChildNode(t),
  theoryTokenPos(t.theoryTokenPos),
  endTokenPos(t.endTokenPos),
  andTokenPos(t.andTokenPos)
{

}

TheoryNode::~TheoryNode()
{
}

BNode*
TheoryNode::copy() const
{
	return new TheoryNode(*this);
}

int
TheoryNode::type()
{
	if(nodeType == -1)
	{
		nodeType = getNewType();
	}
	return nodeType;
}

void
TheoryNode::writeTo(NodeWriter& n) const
{
	n.write("THEORY ");
	n.write(getValue());
	n.write(" ");
	const BNode *child = getChild();
	if(child)
	{
		n.write("IS");
		n.increaseLevel();
		while(child)
		{
			n.newLine();
			child->writeTo(n);

			child = child->getSibling();

			if(child)
			{
				n.write(";");
			}
		}

		n.decreaseAndNewLine();
	}
	n.write("END");

}

};
