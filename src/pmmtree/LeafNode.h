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
#ifndef LEAFNODE_H_
#define LEAFNODE_H_
#include "BNode.h"

namespace theory
{
/**
 * Base class for nodes that are leafs. I.e. that cannot have
 * children nodes, such as identifiers
 */
class LeafNode
: public BNode
{
public:
	LeafNode(int type, const std::string& val);
	LeafNode(const LeafNode&n);
	virtual ~LeafNode();

	virtual void writeTo(NodeWriter& n) const;
	virtual BNode *copy() const;

};
};

#endif /*LEAFNODE_H_*/
