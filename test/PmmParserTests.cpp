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

using namespace std;
using namespace theory;

class PmmParserTests :
	public QObject
{
	Q_OBJECT
private slots:
	void init(void);
	void cleanup(void);

	void testParseFormula_data(void);
	void testParseFormula(void);

	void testParsePmm(void);
	void testParsePmm_data(void);

        void testRange(void);
        void testRange_data(void);
private:
	BNode *bnode;
};

namespace QTest {
    /*!
     * Function that is used to display the values
     * of TextPos elements when a test fails.
     */
    template<>
    char *toString(const TextPos& pos)
    {
        QByteArray ba = "[";
        ba += QByteArray::number(pos.getLine());
        ba += ":";
        ba += QByteArray::number(pos.getColumn());
        ba += "]";
        return qstrdup(ba.data());
    }
}

void PmmParserTests::testRange()
{
    QFETCH(QString, Formula);
    QFETCH(int,     StartLine);
    QFETCH(int,     StartColumn);
    QFETCH(int,     EndLine);
    QFETCH(int,     EndColumn);

    bnode = PmmParser::parseFormula(Formula.toStdString());
    QVERIFY2(bnode != 0, "Unable to parse Formula");

    TextPos expected_start(StartLine, StartColumn);
    TextPos expected_end(EndLine, EndColumn);

    TextPos start, end;
    bnode->getRange(start, end);
    QCOMPARE(start, expected_start);
    QCOMPARE(end, expected_end);
}



void
PmmParserTests::testParseFormula()
{
	QFETCH(QString, Formula);
	bnode = PmmParser::parseFormula(Formula.toStdString());
	QVERIFY(bnode != 0);
}

void
PmmParserTests::testParsePmm()
{
	QFETCH(QString, Pmm);
	bnode = PmmParser::parsePmmString(Pmm.toStdString());
	QVERIFY(bnode != 0);
}

void PmmParserTests::testRange_data()
{
    QTest::addColumn<QString>("Formula");
    QTest::addColumn<int>("StartLine");
    QTest::addColumn<int>("StartColumn");
    QTest::addColumn<int>("EndLine");
    QTest::addColumn<int>("EndColumn");

    //                           12345678901234567
    QTest::newRow("Direct1") << "(a >< b)(x)" << 1 << 1 << 1 << 12;
    QTest::newRow("Direct2") << "     a >< b     " << 1 << 6 << 1 << 12;
    QTest::newRow("Direct3") << "  (  a  ><b )   " << 1 << 3 << 1 << 14;
    QTest::newRow("MultiL1") << "  (   \n"
                                " a   ><   \n"
                                "       b   )\n\n" << 1 << 3 << 3 << 13;
}

void
PmmParserTests::testParsePmm_data()
{
	QTest::addColumn<QString>("Pmm");
	QTest::newRow("PMM 1") << 
		"THEORY csy1 IS\n"
		"  SIGMA(a).(a=b | c) == [a:=b]c\n"
		"END\n";
	QTest::newRow("PMM 2") << "THEORY csy1 END";
	QTest::newRow("PMM 3") << 
		"THEORY csy1 IS\n"
		"  a == b;\n"
		"  X\n"
		"END\n";

	QTest::newRow("PMM 4") <<
		"THEORY csy1 IS\n"
		"  a == b\n"
		"END\n";

	QTest::newRow("PMM 5") <<
		"THEORY csy1 IS\n"
		"  a == [a:=b]c\n"
		"END\n";
	QTest::newRow("PMM 6") <<
		"THEORY csy1 IS\n"
		"  a == [a:=b]c;\n"
		"  X\n"
		"END\n";
	QTest::newRow("PMM 7") <<
		"THEORY csy1 IS\n"
		"  [a:=b]c\n"
		"END\n";
	QTest::newRow("ticket445") <<
		"THEORY tt IS\n"
		"	(binhyp(c: C*{a})) &\n"
		"	(blvar(Q)) &\n"
		"	(Q\\(c: C*{a}))\n"
		"	=>\n"
		"	prj2(A,B)(c) == a\n"
		"   END\n";
}

void
PmmParserTests::init(void)
{
	bnode = 0;
}

void
PmmParserTests::cleanup()
{
	delete bnode;
}

void 
PmmParserTests::testParseFormula_data()
{
	QTest::addColumn<QString>("Formula");
	QTest::newRow("SIGMA1") << "SIGMA(a).(a=b | c) == [a:=b]c";
	QTest::newRow("SIGMA2") << "SIGMA(a).(a=b|c)";
	QTest::newRow("SIGMA3") << "SIGMA(xx).(xx : 0..10 | xx * xx)";
	QTest::newRow("Formula1") << "a & b => c";
	QTest::newRow("Formula2") << "binhyp(x = y + 2) & x = 2 => y = 0";
	QTest::newRow("Forall")   << "!x.(x : Y => Z)";
	QTest::newRow("Exists")   << "#y.(xx : E & y = xx)";
	QTest::newRow("Forall2")  << "!x. (b => [f:=a]p)";
	QTest::newRow("Forall3")  << "!(x,y).(x : E & y : E => Z)";
	QTest::newRow("Forall4")  << 
		"!a.(b => [f:=a]e) &\n"
		"!f.(e => [a:=f]b) &\n"
		"a\\c &\n"
		"f\\c\n"
		"=>\n"
		"SIGMA(a).(b|c(a)) = SIGMA(f).(e|c(f))";
	QTest::newRow("Forall5")  << "(!x.not(P))";
	QTest::newRow("Forall6")  << "[x:=y]!x.P";
	QTest::newRow("Quantified set") << "{ x | x : NAT & x = 3}";
	QTest::newRow("Quantified set 2") << "{ x, y | y : NAT & x : NAT & x = 3}";

	QTest::newRow("Subst1") << "[a:=f]b";
	QTest::newRow("Subst2") << "[a:=f]b & !a.(e => b)";
	QTest::newRow("Subst3") << "a & [x:=y]z";
	QTest::newRow("Subst4") << "a = [x:=y]z";
	QTest::newRow("Subst5") << "[x,y := a,b]X";
        QTest::newRow("Subst6") << "[x:=a][y:=b]X";
	QTest::newRow("Bdr1")   << 
		"band((bsearch((y = L),(P & p),u)), \n"
		"band((L\\y), \n"
		"(bguard((SUB;RES): bresult([L:=y]!OK.OK),!OK.OK)))) &\n"
		"(bguard((SUB~;RES): bresult([L:=y](P & p => S)),(Q => T)))\n"
		"=>\n"
		"!L.(P & p => S) == (Q => T)\n";
	QTest::newRow("Bdr2") <<
		"((bguard(FindLabX: __fl(rec(L) | l),v))\n"
		"=>\n"
		"rec(L)'l == v)";
	QTest::newRow("Bdr3") << 
		"(bvrb(x))\n"
		"=>\n"
		"SET(x).P = {} == !x.not(P)";
	QTest::newRow("Bdr4") <<
		"(bresult(R & x = y))\n"
		"=>\n"
		"(Goal(l>>x | l>>y | R))";
	QTest::newRow("Bdr5") << "__fl(rec(x>>v) | l)";
	QTest::newRow("Bdr6") << 
		"(bcall((FLAT;RES): bresult(bflat(P & r'x: E))))\n"
		"=>\n"
		"(__labrec1(r | struct(x>>E) | P))";
	QTest::newRow("Bdr7") <<
		"(bsearch((E = y),(P & R),Q)) &\n"
		"(y\\E) &\n"
		"(bsearch(y,(w,x),z)) &\n"
		"(bguard((SUB;RES): bresult([y:=E]Q),S)) &\n"
		"(bnot(bpattern(S,[a:=b]T)))\n"
		"=>\n"
		"#(w,x).(P & R) == #z.[y:=E]Q";
	QTest::newRow("Bdr8") << "({a}b == {a}(b))";
	QTest::newRow("Bdr9") << 
		"(bsearch(i>>{},(L,l>>E),R))\n"
		"=>\n"
		"struct(L,l>>E) == {}";
	QTest::newRow("Bdr10") <<
		"(x\\A) &\n"
		"(!x.not(P & x: A))\n"
		"=>\n"
		"(A/\\SET(x).P = {})";
	QTest::newRow("Bdr11") << 
		"(bsearch((y = E),(P & btrue),(Q & btrue))) &\n"
		"(y\\E) &\n"
		"(bsearch(y,(w,x),z)) &\n"
		"(WD(expr(E),Z)) &\n"
		"(#z.[y:=E]Q)\n"
		"=>\n"
		"(#(w,x).P)";
	QTest::newRow("Bdr12") <<
		"(a\\A) &\n"
		"(A = {})\n"
		"=>\n"
		"(!a.not(a: A))";
	QTest::newRow("Bdr13") <<
		"(#x.not(P))\n"
		"=>\n"
		"(not(!x.P))";
	QTest::newRow("Bdr14") <<
		"band((binhyp(a = b)), \n"
		"(bsubfrm(b,toto,B,(R,?)))) &\n"
		"(bguard(SubFrmX: SubFrmG(b,a,B),C)) &\n"
		"(bguard(attempt_to_prove: a_t_t_e_m_p_t__t_o__p_r_o_v_e(C | Curr)))\n"
		"=>\n"
		"(B)";
	QTest::newRow("Bdr15") <<
		"(!x.(a => b)) &\n"
		"(not(c)) &\n"
		"(bmatch(x,b,c,e)) &\n"
		"(bguard((SUB;RES): bresult([x:=e]not(a)),not(A))) &\n"
		"(bnot(band(bsubfrm(P,btrue,A,Q),bmatch(x,b,P,E)))) &\n"
		"(bguard((SimplifyX~;FLAT;RES): bresult(bflat(not(A))),O))\n"
		"=>\n"
		"(O)";
	QTest::newRow("Bdr16") <<
		"(not(a: SET(x).P)) &\n"
		"(bguard((SUB;RES): bresult([x:=a]not(P)),R)) &\n"
		"(bnot(bpattern(R,[y:=z]S)))\n"
		"=>\n"
		"(R)";
	QTest::newRow("Bdr17") <<
		"(not(a: POW(SET(x).P))) &\n"
		"(bfresh(x,not(a: POW(SET(x).P)),y))\n"
		"=>\n"
		"(#y.(y: a & [x:=y]not(P)))";
	QTest::newRow("Paren1") << "f(x)(y) == z";
	QTest::newRow("Bdr18") << "(a\\/{b})c == (a\\/{b})(c)";
	QTest::newRow("Bdr19") << "{FALSE|->a}[{TRUE}] == {}";
	QTest::newRow("Bdr20") << "(not(a: A[c])) & (not(a: {b}[c])) => (not(a: (A\\/{b})[c]))";
	QTest::newRow("Bdr21") << "{(x,y)|->z}~[{z}] == {x|->y}";
	QTest::newRow("Bdr22") << "((a\\/{b})c == (a\\/{b})(c))";
	QTest::newRow("Rec1")  << "(x'y)";
	QTest::newRow("Rec2")  << "(x'y == z)";
	QTest::newRow("BDR STS1") << "dom( d |>> {e}) = dom (d |>> {e})~";
	QTest::newRow("Bdr STS2") << "([a]~: d) == ({1|->a}~: d)";
	QTest::newRow("Inv2") << "([a]~: d)";
	QTest::newRow("Inv3") << "({1|->a}~: d)";
	QTest::newRow("Inv") << "{a |->b}~ == x";
}


int main(int argc, char **argv)
{
	PmmParserTests test;
	return QTest::qExec(&test, argc, argv);
}

#include "moc_PmmParserTests.cpp"
