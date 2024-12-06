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
#ifndef PMMPARSER_H_
#define PMMPARSER_H_
#include <iostream>
#include <string>


namespace theory
{
class BNode;
class ErrorHandler;
class PmmFactory;
class PmmFile;
class Parser;
class Scanner;
class TheoryNode;
/**
 * Class that can be used to parse pmm files or pmm
 * formulas
 */
class PmmParser
{
public:
	virtual ~PmmParser();

	/**
	 * Parses the given stream as a pmm file
	 */
	static PmmFile* parsePmm(std::istream& stream, const std::string& stream_name, ErrorHandler& handler);
    /**
     * Parses the given theory as a pmm file
     */
    static BNode* parseTheory(std::istream& stream, const std::string& stream_name, ErrorHandler& handler);
    /**
	 * Parses the given formula as a pmm file
	 */
	static BNode* parseFormula(std::istream& stream, const std::string& stream_name, ErrorHandler& handler);

	/**
	 * Parses the given pmm file.
	 *
	 * @param file the file name to parse
	 * @param handler the error handler that should be used
	 * @return the parsed file, or NULL if an error occured
	 */
	static PmmFile* parsePmmFile(const std::string& file, ErrorHandler& handler);

	static PmmFile* parsePmmString(const std::string& str, ErrorHandler& handler);

	static PmmFile *parsePmmString(const std::string& str);

    /**
     * Parses the given theory
     *
     * @param theory a string containing the theory to parse
     * @return the parsed theory, or null if an error occured
     */
    static BNode *parseTheory(const std::string& theory, ErrorHandler& handler);
	/**
	 * Parses the given formula
	 *
	 * @param formula a string containing the formula to parse
	 * @return the parsed formula, or null if an error occured
	 */
	static BNode *parseFormula(const std::string& formula, ErrorHandler& handler);
	/**
	 * Parses the given formula
	 */
	static BNode *parseFormula(const std::string& formula);


private:
	PmmParser(std::istream* str, const std::string& str_name,
			ErrorHandler *handler);

	PmmFile *parseFile();
	BNode *parseFormula();
    TheoryNode *parseTheory();

	Parser *parser;
	Scanner *scanner;
	PmmFactory *factory;
};
};

#endif /*PMMPARSER_H_*/
