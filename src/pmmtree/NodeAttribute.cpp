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
#include "NodeAttribute.h"

namespace theory
{

    NodeAttribute::~NodeAttribute()
    {
    }


    NodeAttribute* NodeAttribute::getNext(const std::string &attribute_name) const
    {
        NodeAttribute *nxt = getNext();

        while(nxt)
        {
            if(nxt->getName() == attribute_name)
            {
                return nxt;
            }

            nxt = nxt->getNext();
        }

        return nxt;
    }
}
