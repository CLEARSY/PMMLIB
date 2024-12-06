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
#ifndef TEXT_POS_H
#define TEXT_POS_H

namespace theory
{
    /*!
     * Class holding line and column information
     */
    class TextPos
    {
    public:
        TextPos();
        TextPos(int line, int column);
        TextPos(const TextPos& c);

        TextPos& operator = (const TextPos&);

        bool operator == (const TextPos&) const;
        bool operator < (const TextPos&) const;

        int getLine() const { return line; }
        int getColumn() const { return column; }

        void setPos(int l, int c) { line = l; column = c; }

        void setLine(int l)   { line = l; }
        void setColumn(int c) { column = c; }

        bool isValid() const;

        TextPos& operator ++ () { ++column; return *this; }
        TextPos  operator ++ (int);

        void append(char c);
    private:
        int line;
        int column;
    };

    TextPos makeInvalidTextPos();

    TextPos makeTextPosByShiftingTheColumn(const TextPos &textPos, int shift);
}

#endif // TEXT_POS_H
