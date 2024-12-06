#include "ParenthesisAttribute.h"

namespace theory
{
    ParenthesisAttribute::ParenthesisAttribute(char val, const TextPos& opening, const TextPos& closing)
        : openingValue(val),
         openingPos(opening),
         closingPos(closing)
    { }

    std::string ParenthesisAttribute::getName() const
    {
        return getAttributeName();
    }

    std::string ParenthesisAttribute::getAttributeName()
    {
        return "ParenthesisAttribute";
    }
};
