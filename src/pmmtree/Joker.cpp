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
#include "Joker.h"
#include "JokerInstanciation.h"

namespace theory
{
Joker::Joker(const std::string& value)
: LeafNode(NODE_JOKER, value)
{
}

Joker::Joker(char id)
    : LeafNode(NODE_JOKER, std::string(1, id))
{
}

Joker::Joker(const Joker& j)
: LeafNode(j)
{

}

Joker::~Joker()
{
}

char
Joker::getJokerChar() const
{
	return getValue()[0];
}

BNode*
Joker::copy() const
{
	return new Joker(*this);
}

BNode *
Joker::instanciatedCopy(const JokerInstanciation *j) const
{
    if(j)
    {
        const BNode *instanciated = j->getInstanciation(getJokerChar());
        if(instanciated)
        {
            return instanciated->copy();
        }
    }

    return copy();
}
};
