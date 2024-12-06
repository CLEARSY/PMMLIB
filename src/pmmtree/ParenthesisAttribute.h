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
#ifndef PARENTHESIS_ATTRIBUTE_H
#define PARENTHESIS_ATTRIBUTE_H

#include "NodeAttribute.h"
#include "TextPos.h"

namespace theory
{
    /*!
     * Attribute that is used to indicate that parenthesis where surounding the
     * given node.
     * It contains the type of the parenthesis as well as their positions.
     */
    class ParenthesisAttribute
        : public NodeAttribute
    {
    public:
        ParenthesisAttribute(char val,
                             const TextPos& opening,
                             const TextPos& closing);

        std::string getName() const;

        void setOpeningPos(const TextPos& p)  { openingPos = p; }
        void setClosingPos(const TextPos& p)  { closingPos = p; }
        void setOpeningValue(char c)          { openingValue = c; }

        const TextPos& getOpeningPos() const { return openingPos; }
        const TextPos& getClosingPos() const { return closingPos; }
        char getOpeningValue() const { return openingValue; }

        static std::string getAttributeName();
    private:
        char openingValue;
        TextPos openingPos;
        TextPos closingPos;
    };
};
#endif // PARENTHESIS_ATTRIBUTE_H
