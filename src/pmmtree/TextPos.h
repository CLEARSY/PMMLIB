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
