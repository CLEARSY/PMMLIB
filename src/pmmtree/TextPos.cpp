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
