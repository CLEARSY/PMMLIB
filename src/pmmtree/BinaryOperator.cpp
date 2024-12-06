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
#include <common.h>
#include <pmmtree/NodeWriter.h>
#include "BinaryOperator.h"
#include "ParenthesisAttribute.h"

namespace theory
{
BinaryOperator::PriorityTable*
BinaryOperator::priorities = 0;

BinaryOperator::BinaryOperator(const std::string& value, BNode *left,
                               BNode *right, int type)
    : ChildNode(NODE_BINARY_OPERATOR, value, left), operatorType(type)
{
    if(left)
    {
        left->setSibling(right);
    }
}

BinaryOperator::BinaryOperator(const std::string& value, BNode *left,
                               BNode *right)
    : ChildNode(NODE_BINARY_OPERATOR, value, left), operatorType(DEFAULT)
{
    if(left)
    {
        left->setSibling(right);
    }
    // fixes the operator type
    if(value == "[]")
    {
        operatorType = NON_DISPLAYED;
    }
    else if(value == "(" || value == "[")
    {
        operatorType = IMG;
    }
    else if(value == "!" || value == "#" || value == "%") {
        operatorType = QUANTIFIED;
    }
    else if(value == "SIGMA" || value == "PI"  || value == "UNION" || value == "INTER" || value == "SET")
    {
        operatorType = PARENTHEZED_QUANTIFIED;
    }
    else if(value == ":" || value == "=" || value == "&" || value == "or" || value == "=>" || value == "<:"
            || value == "mod" || value == "|" || value == "<->" || value == "||"
            || value == "+->"  || value == "-->"  || value == "+->"  || value == ">->"
            || value == "-->>"  || value == "-+>>"  || value == ">+>>"  || value == ">->>"
            || value == "=="
            || value == "rplus" || value == "rminus" ||  value == "rmul" ||  value == "rdiv" ||  value == "rpow"
            || value == "rle" || value == "rlt" ||  value == "rmul" ||  value == "rge" ||  value == "rgt")
    {
        operatorType |= SPACE_BEFORE | SPACE_AFTER;
    }
    else if(value == ";")
    {
        operatorType |= SPACE_AFTER;
    }

    if(value == "&" || value == "or")
    {
        operatorType |= CR_AFTER_TOPLEVEL;
    }

    if(value == "=>")
    {
        operatorType |= CR_AFTER;
    }
    if(value == "=>")
    {
        operatorType |= CR_BEFORE;
    }
}

int
BinaryOperator::getPriority() const
{
    if(!priorities)
    {
        priorities = new PriorityTable;
        (*priorities)["|"] = 10;
        (*priorities)[":="] = 5;
        (*priorities)["::"] = 5;
        (*priorities)[";"] = 20;
        (*priorities)["||"] = 20;
        (*priorities)["=="] = 60;
        (*priorities)["=>"] = 30;
        (*priorities)["&"] = 40;
        (*priorities)["or"] = 40;
        (*priorities)[":"] = 60;
        (*priorities)["<=>"] = 60;
        (*priorities)["="] = 60;
        (*priorities)["<:"] = 110;
        (*priorities)["<<:"] = 110;
        (*priorities)["/<:"] = 110;
        (*priorities)["/<<:"] = 110;
        (*priorities)[","] = 115;

        (*priorities)["+->"] = 120;
        (*priorities)["+->>"] = 120;
        (*priorities)["-->"] = 120;
        (*priorities)["-->>"] = 120;
        (*priorities)["<->"] = 120;
        (*priorities)[">+>"] = 120;
        (*priorities)[">->"] = 120;
        (*priorities)[">+>>"] = 120;
        (*priorities)[">->>"] = 120;
        (*priorities)["\\"] = 160;
        (*priorities)["->"] = 160;
        (*priorities)["/:"] = 160;
        (*priorities)["/="] = 160;
        (*priorities)["/\\"] = 160;
        (*priorities)["/|\\"] = 160;
        (*priorities)["<"] = 160;
        (*priorities)["<."] = 160;
        (*priorities)["rlt"] = 160;
        (*priorities)["<+"] = 160;
        (*priorities)["<<<"] = 160;
        (*priorities)["<-"] = 160;
        (*priorities)["<<|"] = 160;
        (*priorities)["<="] = 160;
        (*priorities)["<=."] = 160;
        (*priorities)["rle"] = 160;
        (*priorities)["<|"] = 160;
        (*priorities)[">"] = 160;
        (*priorities)["rgt"] = 160;
        (*priorities)[">."] = 160;
        (*priorities)["><"] = 160;
        (*priorities)[">="] = 160;
        (*priorities)[">=."] = 160;
        (*priorities)["rge"] = 160;
        (*priorities)["\\/"] = 160;
        (*priorities)["\\|/"] = 160;
        (*priorities)["^"] = 160;
        (*priorities)["|->"] = 160;
        (*priorities)["|>"] = 160;
        (*priorities)["|>>"] = 160;
        (*priorities)[".."] = 170;
        (*priorities)[">>"] = 170;
        (*priorities)["+"] = 180;
        (*priorities)["+."] = 180;
        (*priorities)["rplus"] = 180;
        (*priorities)["-"] = 180;
        (*priorities)["rminus"] = 180;
        (*priorities)["-."] = 180;
        (*priorities)["*"] = 190;
        (*priorities)["rmul"] = 190;
        (*priorities)["*."] = 190;
        (*priorities)["/"] = 190;
        (*priorities)["/."] = 190;
        (*priorities)["mod"] = 190;
        (*priorities)["rdiv"] = 190;
        (*priorities)["**"] = 200;
        (*priorities)["rpow"] = 200;
        (*priorities)["."] = 220;

        (*priorities)[",,"] = 160;

        (*priorities)["[]"] = 0;

        (*priorities)["!"] = 250;
        (*priorities)["#"] = 250;
        (*priorities)["%"] = 250;
        (*priorities)["SET"]   = 250;
        (*priorities)["SIGMA"] = 250;
        (*priorities)["PI"]    = 250;
        (*priorities)["UNION"] = 250;
        (*priorities)["INTER"] = 250;

        (*priorities)["("] = 260;

        (*priorities)["'"] = 270;

        (*priorities)["$"] = 280;
    }

    PriorityTable::iterator it = priorities->find(getValue());
    if(it != priorities->end())
    {
        return (*it).second;
    }
    else
    {
        return MaxPriority;
    }
}

BinaryOperator::BinaryOperator(const BinaryOperator& b)
    : ChildNode(b), operatorType(b.operatorType)
{
}


BNode*
BinaryOperator::copy() const
{
    return new BinaryOperator(*this);
}

void
BinaryOperator::writeNode(const BNode *node, NodeWriter& writer, bool parenthesis) const
{
    if(parenthesis)
    {
        writer.write("(");
        writer.increaseLevel();
    }
    node->writeTo(writer);
    if(parenthesis)
    {
        writer.decreaseLevel();
        writer.write(")");
    }
}

bool BinaryOperator::isUnnormalisedSet() const
{
    if(getValue() == "SET")
    {
        const ParenthesisAttribute *p = (ParenthesisAttribute*)getAttribute(ParenthesisAttribute::getAttributeName());
        while(p)
        {
            char c = p->getOpeningValue();
            if(c == '{')
            {
                return true;
            }

            p = (ParenthesisAttribute*)p->getNext(ParenthesisAttribute::getAttributeName());
        }
    }

    return false;
}

/* Le problème de parenthésage est insoluble avec uniquement le principe de priorité:
 * pour écrire a$1(b) et non (a$1)(b), if faut que priority("(") <= priority("$")
 * pour écrire %(a$O).(b|c) et non %a$0.(b|c), if faut que priority("$") < priority("%")
 * pour écrire (%a.(b|c))(d) et non %a.(b|c)(d), if faut que priority("%") < priority("(")
 * J'ai laissé :
 * priority("(") <= priority("$")
 * et priority("%") < priority("(")
 * et j'ai ajouté un hack pour traiter le cas des quantificateurs avec variables $.
 */
void
BinaryOperator::writeTo(NodeWriter& n) const
{
    const BNode *left = getChild();
    const BNode *right = getChild();
    const BinaryOperator* leftOp;
    if(left)
    {
        right = left->getSibling();
    }

    if(left && right)
    {
        int priority = getPriority();
        int left_priority = left->getPriority();
        int right_priority = right->getPriority();

        bool parenthesis_left = left_priority < priority;
        bool parenthesis_right = right_priority <= priority;

        std::string written_value = getValue();
        if(written_value == ",,")
        {
            written_value = ",";
        }

        switch(operatorType)
        {
        case IMG:
            writeNode(left, n, parenthesis_left);
            n.write(written_value);
            n.increaseLevel();
            right->writeTo(n);
            n.decreaseLevel();
            n.write(getClosingValue());
            break;
        case QUANTIFIED:
            n.write(written_value);
            leftOp = dynamic_cast<const BinaryOperator*>(left);
            if (leftOp != NULL && leftOp->getValue() == "$") {
                parenthesis_left = true;
            }
            writeNode(left, n, parenthesis_left);
            n.write(".(");
            n.increaseLevel();
            right->writeTo(n);
            n.decreaseLevel();
            n.write(")");

            break;
        case PARENTHEZED_QUANTIFIED :
            if(isUnnormalisedSet())
            {
                n.write("{");
                left->writeTo(n);
                n.write(" | ");
                n.increaseLevel();
                right->writeTo(n);
                n.decreaseLevel();
                n.write("}");
            }
            else
            {
                n.write(written_value);
                n.write("(");
                n.increaseLevel();
                writeNode(left, n, false);
                n.decreaseLevel();
                n.write(").(");
                n.increaseLevel();
                right->writeTo(n);
                n.decreaseLevel();
                n.write(")");
            }
            break;
        case NON_DISPLAYED:
            writeNode(left, n, parenthesis_left);
            writeNode(right, n, parenthesis_right);
            break;
        default:
            writeNode(left, n, parenthesis_left);
            if(operatorType & SPACE_BEFORE)
            {
                n.write(" ");
            }
            if((operatorType & CR_BEFORE) && !n.singleLine())
            {
                n.newLine();
            }
            n.write(written_value);
            if(operatorType & SPACE_AFTER)
            {
                n.write(" ");
            }
            if((operatorType & CR_AFTER) && !n.singleLine())
            {
                n.newLine();
            }

            if((operatorType & CR_AFTER_TOPLEVEL) && !n.singleLine())
            {
                if(n.getLevel() == 0)
                {
                    n.newLine();
                }
            }

            writeNode(right, n, parenthesis_right);
            break;
        }
    }
}
};
