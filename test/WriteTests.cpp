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
#include <pmmparser/PmmFile.h>
#include <pmmtree/StreamWriter.h>
#include <sstream>

using namespace std;
using namespace theory;

class WriteTests :
        public QObject
{
        Q_OBJECT
private slots:

        void testWrite_data(void);
        void testWrite(void);

};

void WriteTests::testWrite_data()
{
    QTest::addColumn<QString>("read");
    QTest::addColumn<QString>("rewritten");

    QTest::newRow("plus1") << "a + (B + c)" << "a+(B+c)";
    QTest::newRow("plus2") << "(a + b) + c" << "a+b+c";
    QTest::newRow("img1")  << "K[{c}]" << "K[{c}]";
    QTest::newRow("img2")  << "(K)~[{c}]" << "(K)~[{c}]";
    QTest::newRow("img3") << "(K;L)~[E]" << "(K; L)~[E]";
    QTest::newRow("img4") << "(K;L)[E]" << "(K; L)[E]";
    QTest::newRow("unaryminus") << "-(2+3)" << " -(2+3)";
    QTest::newRow("unaryminus2") << "-2+3" << " -2+3";
    QTest::newRow("compset1") << "{ x | x :E }" << "{x | x : E}";
    QTest::newRow("lambda1") << "%x.(x:NAT|x+1)" << "%x.(x : NAT | x+1)";
    QTest::newRow("union1") << "union({x | x = 2})" << "union({x | x = 2})";
    QTest::newRow("funimage1") << "x = f(x)" << "x = f(x)";
    QTest::newRow("funimage2") << "f(x)" << "f(x)";
    QTest::newRow("set1") << "SET(x).(x : E)" << "SET(x).(x : E)";
    QTest::newRow("dollar1") << "#toto$1.(toto$1 : E)" <<  "#(toto$1).(toto$1 : E)";
    QTest::newRow("dollar2") << "#(xx, xx$1).(xx$1 : E & xx : F)" << "#(xx,xx$1).(xx$1 : E & xx : F)";
    QTest::newRow("lambda1") << "%xx.(xx : NAT | xx +1)(4)" << "(%xx.(xx : NAT | xx+1))(4)";
    QTest::newRow("lambdaDollar") << "%(bcpi$0).(bcpi$0 : NAT | bcpi$0)" << "%(bcpi$0).(bcpi$0 : NAT | bcpi$0)";
    QTest::newRow("subst1") << "[x:=y]a" << "[x:=y]a";
    QTest::newRow("seqBug") << "[ x ]1"  << "[x](1)";
    QTest::newRow("seqBug2") << "[a]b" << "[a](b)";
    QTest::newRow("subst2") << "[x:=y][z:=w][a]1" << "[x:=y][z:=w][a](1)";
    QTest::newRow("rec1") << "a'b'c" << "a'b'c";
    QTest::newRow("ticket915-lambda-1") << "(%xx.(P | E))~" << "(%xx.(P | E))~";
    QTest::newRow("ticket915-lambda-2") << "(%xx.(P | E))[F]" << "(%xx.(P | E))[F]";
    QTest::newRow("ticket1315-rewrite") << "(a & (b & c)) == (a & b & c)" << "(a & (b & c)) == (a & b & c)";
    QTest::newRow("ticket1318") << "blvar(Q) & \n"
                                   "Q\\(a,b,c) \n"
                                   "=> \n"
                                   "a : b\\/c==(a : b or a : c)" << "blvar(Q) & "
                                   "Q\\(a,b,c) "
                                   "=> "
                                   "a : b\\/c == (a : b or a : c)";
    QTest::newRow("ticket832-1") << "(a => not(b)) == (not(a & b)) " << "(a => not(b)) == not(a & b)";
    QTest::newRow("ticket832-2") << "(a => b) == (not(a) or b)" << "(a => b) == (not(a) or b)";

    QTest::newRow("ticket1114") << "prj1(a ,(b --> c))" << "prj1(a,(b --> c))";
    QTest::newRow("rewrOp")     << "(0 = 1+a-b) == (b = a+1)"
                                << "0 = 1+a-b == (b = a+1)";
}

void WriteTests::testWrite()
{
    QFETCH(QString, read);
    QFETCH(QString, rewritten);

    BNode *formula = PmmParser::parseFormula(read.toStdString());
    QVERIFY(formula != 0);

    std::ostringstream str;
    str << *formula;
    std::string printed = str.str();
    QString actual = QString::fromStdString(printed);

    QCOMPARE(actual, rewritten);

    delete formula;
}

int main(int argc, char **argv)
{
        WriteTests test;
        return QTest::qExec(&test, argc, argv);
}

#include "moc_WriteTests.cpp"
