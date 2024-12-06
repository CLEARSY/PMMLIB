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
#include "TextPos.h"

#define COLUMN_START 1
#define LINE_START   1

namespace theory
{
    TextPos::TextPos()
            : line(LINE_START), column(COLUMN_START)
    { }

    TextPos::TextPos(int l, int c)
            : line(l), column(c)
    { }

    TextPos::TextPos(const TextPos& lc)
            : line(lc.line), column(lc.column)
    { }

    TextPos& TextPos::operator =(const TextPos& lc)
                               {
        line = lc.line;
        column = lc.column;
        return *this;
    }

    bool TextPos::operator == (const TextPos& lc) const
                            {
        return line == lc.line &&
                column == lc.column;
    }

    bool TextPos::operator < (const TextPos& lc) const
    {
        if(line < lc.line)
        {
            return true;
        }
        else if(line == lc.line)
        {
            return column < lc.column;
        }
        else
        {
            return false;
        }
    }

    bool TextPos::isValid() const {
        return line >= LINE_START && column >= COLUMN_START;
    }

    void TextPos::append(char c)
    {
        if(c == '\n')
        {
            ++line;
            column = COLUMN_START;
        }
        else
        {
            ++column;
        }
    }

    TextPos TextPos::operator ++(int)
    {
        TextPos ret(*this);
        ++column;
        return ret;
    }

    TextPos makeInvalidTextPos() {
        return TextPos(LINE_START - 1, COLUMN_START - 1);
    }

    TextPos makeTextPosByShiftingTheColumn(const TextPos &textPos, int shift) {
        return TextPos(textPos.getLine(), textPos.getColumn() + shift);
    }
}
