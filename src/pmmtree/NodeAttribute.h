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
#ifndef NODE_ATTRIBUTE_H
#define NODE_ATTRIBUTE_H
#include <string>

namespace theory {

class NodeAttribute
{
public:
    virtual ~NodeAttribute();

    /**
     * Return the name of the attribute
     */
    virtual std::string getName() const = 0;

    /**
     * Return the next attribute in the list
     *
     * @return the next attribute
     */
    NodeAttribute *getNext() const   { return next; }

    /**
     * Set the next attribute
     *
     * @param nxt the next attribute
     */
    void setNext(NodeAttribute *nxt) { next = nxt; }

    /**
     * Returns the next attribute with the given name.
     *
     * @param attribute_name The name of the searched attribute.
     */
    NodeAttribute *getNext(const std::string& attribute_name) const;

private:
    /**
     * Next attribute in the linked list
     */
    NodeAttribute *next;
};

}

#endif // NODE_ATTRIBUTE_H
