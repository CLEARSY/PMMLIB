/******************************* CLEARSY **************************************
This file is part of BPARSERS
    Copyright © CLEARSY 2008-2020 (contact@clearsy.com)

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
#ifndef JOKER_H_
#define JOKER_H_

#include "LeafNode.h"
namespace theory
{
class Joker : public LeafNode
{
public:
	Joker(const std::string& value);
	Joker(char);
	Joker(const Joker& j);
	virtual ~Joker();

	BNode *copy() const;

        BNode *instanciatedCopy(const JokerInstanciation *j) const;

	char getJokerChar() const;
};
};

#endif /*JOKER_H_*/
