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
#include <QtCore>
#include <QtTest/QtTest>
#include <pmmparser/PmmParser.h>
#include <pmmtree/BNode.h>
#include <pmmtree/NodeAttribute.h>
#include <pmmtree/JokerInstanciation.h>
#include <pmmparser/PmmFile.h>
#include <pmmtree/StreamWriter.h>
#include <pmmtree/Joker.h>

using namespace std;
using namespace theory;

class IntAttribute : public NodeAttribute
{
public:
    IntAttribute(int v) : val(v) { }

    int getValue() { return val; }
    std::string getName() const { return "IntAttribute"; }

private:
    int val;
};

class StringAttribute : public NodeAttribute
{
public:
    StringAttribute(const std::string& s) : val(s) { }
    std::string getName() const { return "StringAttribute"; }

private:
    std::string val;
};

class AttributesTests :
        public QObject
{
        Q_OBJECT
private slots:
        void init(void);
        void cleanup(void);

        void test1(void);
//        void test3(void);
//
//        void testFails(void);
//        void test2(void);
    private:
        BNode *node;
};

void AttributesTests::init()
{
    node = new Joker("t");
}

void AttributesTests::cleanup()
{
    delete node;
}

void AttributesTests::test1()
{
    StringAttribute *sattr = new StringAttribute("Hello");
    IntAttribute    *iattr = new IntAttribute(12);

    node->addAttribute(sattr);
    node->addAttribute(iattr);

    NodeAttribute *t = node->getAttribute("test");

    QVERIFY(t == NULL);

    t = node->getAttribute("StringAttribute");
    QVERIFY(t != NULL);

    StringAttribute *sa = dynamic_cast<StringAttribute*>(t);
    QVERIFY(sa != NULL);
    QVERIFY(sa == sattr);

    t = node->getAttribute("IntAttribute");
    QVERIFY(t != NULL);
    QVERIFY(t == iattr);

    node->removeAttribute("StringAttribute");
    t = node->getAttribute("StringAttribute");
    QVERIFY(t == NULL);
    t = node->getAttribute("IntAttribute");
    QVERIFY(t == iattr);

}

int main(int argc, char **argv)
{
        AttributesTests test;
        return QTest::qExec(&test, argc, argv);
}

#include "moc_AttributesTests.cpp"
