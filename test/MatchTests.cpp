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
#include <pmmtree/JokerInstanciation.h>
#include <pmmparser/PmmFile.h>
#include <pmmtree/StreamWriter.h>

using namespace std;
using namespace theory;

class MatchTests :
	public QObject
{
	Q_OBJECT
private slots:
	void init(void);
	void cleanup(void);

	void test1(void);
	void test2(void);
	void test3(void);

	void testFails(void);
private:
	JokerInstanciation *jokers;
	BNode *pattern;
	BNode *matched;
};

void
MatchTests::init()
{
	jokers = new JokerInstanciation;
	pattern = 0;
	matched = 0;
}

void
MatchTests::cleanup()
{
	delete jokers;
	delete pattern;
	delete matched;
}

void
MatchTests::test1()
{
	pattern = PmmParser::parseFormula("x");
	matched = PmmParser::parseFormula(" a => b");

	QVERIFY(jokers->match(pattern, matched) >= 0);
	QVERIFY(jokers->isInstanciated('x'));
	QVERIFY(!jokers->isInstanciated('a'));
	QVERIFY(!jokers->isInstanciated('b'));
}

void
MatchTests::test2()
{
	pattern = PmmParser::parseFormula("x = y");
	matched = PmmParser::parseFormula(" a = b + c");

	QVERIFY(jokers->match(pattern, matched) >= 0);
	QVERIFY(jokers->isInstanciated('x'));
	QVERIFY(jokers->isInstanciated('y'));
	QVERIFY(!jokers->isInstanciated('a'));
	QVERIFY(!jokers->isInstanciated('b'));
	QVERIFY(!jokers->isInstanciated('c'));
}

void
MatchTests::test3()
{
	pattern = PmmParser::parseFormula("(x = y)");
	matched = PmmParser::parseFormula(" a = b + c");

	QVERIFY(jokers->match(pattern, matched) >= 0);
	QVERIFY(jokers->isInstanciated('x'));
	QVERIFY(jokers->isInstanciated('y'));
	QVERIFY(!jokers->isInstanciated('a'));
	QVERIFY(!jokers->isInstanciated('b'));
	QVERIFY(!jokers->isInstanciated('c'));
}

void
MatchTests::testFails()
{
	pattern = PmmParser::parseFormula("x = z");
	matched = PmmParser::parseFormula(" a => b");

	QVERIFY(jokers->match(pattern, matched) == -1);
}

int main(int argc, char **argv)
{
	MatchTests test;
	return QTest::qExec(&test, argc, argv);
}

#include "moc_MatchTests.cpp"
