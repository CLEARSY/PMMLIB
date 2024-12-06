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
