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
#include <pmmtree/ErrorHandler.h>
#include <pmmtree/DefaultErrorHandler.h>
#include "PmmParser.h"
#include "Parser.h"
#include "Scanner.h"

namespace theory
{

PmmParser::PmmParser(std::istream* stream, const std::string& stream_name,
		ErrorHandler *handler)
{
	scanner = new Scanner(stream);
	parser = new Parser(scanner);

	factory = new PmmFactory();

	parser->setHandler(handler);

	parser->setFileName(stream_name);
	parser->errors->setFileName(stream_name);
	parser->errors->setErrorHandler(handler);
}

PmmParser::~PmmParser()
{
	delete factory;
        delete scanner;
        delete parser;
}

PmmFile *
PmmParser::parseFile()
{
	parser->Parse();
	return parser->parsedFile;
}

BNode*
PmmParser::parseFormula()
{
	BNode *result = 0;
	parser->init();
        parser->Implication(result);
	return result;
}

TheoryNode*
PmmParser::parseTheory()
{
    TheoryNode *result = 0;
    parser->init();
        parser->Theory(result);
    return result;
}

/**
 * Parses the given stream as a pmm file
 */
PmmFile*
PmmParser::parsePmm(std::istream& stream, const std::string& stream_name, ErrorHandler& handler)
{
	PmmParser parser(&stream, stream_name, &handler);
	PmmFile *result =  parser.parseFile();
	if(handler.hasErrors())
	{
		//delete result;
		result = 0;
	}

	return result;
}

/**
 * Parses the given theory as a pmm file
 */
BNode*
PmmParser::parseTheory(std::istream& stream, const std::string& stream_name, ErrorHandler& handler)
{
    PmmParser parser(&stream, stream_name, &handler);
    BNode *result =  parser.parseTheory();
    if(handler.hasErrors())
    {
//		delete result;
        result = 0;
    }
    return result;
}

/**
 * Parses the given formula as a pmm file
 */
BNode*
PmmParser::parseFormula(std::istream& stream, const std::string& stream_name, ErrorHandler& handler)
{
	PmmParser parser(&stream, stream_name, &handler);
	BNode *result =  parser.parseFormula();
	if(handler.hasErrors())
	{
//		delete result;
		result = 0;
	}
	return result;
}

PmmFile*
PmmParser::parsePmmFile(const std::string& file_name, ErrorHandler& handler)
{
	PmmFile *result = 0;
    std::ifstream *f=new std::ifstream(file_name.c_str(), std::ios::binary);
	if(f->is_open())
	{
		result = parsePmm(*f, file_name, handler);
		f->close();
	}
	else
	{
		handler.error("Cannot open file", file_name, ErrorHandler::UNDEFINED, ErrorHandler::UNDEFINED);
	}

	delete f;

	return result;
}

BNode *
PmmParser::parseTheory(const std::string& theory, ErrorHandler& handler)
{
    std::istringstream stream(theory);
    return parseTheory(stream, "", handler);
}

BNode *
PmmParser::parseFormula(const std::string& formula, ErrorHandler& handler)
{
	std::istringstream stream(formula);
	return parseFormula(stream, "", handler);
}

BNode *
PmmParser::parseFormula(const std::string& formula)
{
	DefaultErrorHandler handler(false, false);
	return parseFormula(formula, handler);
}

PmmFile*
PmmParser::parsePmmString(const std::string& str, ErrorHandler& handler)
{
	std::istringstream stream(str);
	return parsePmm(stream, "", handler);
}

PmmFile *
PmmParser::parsePmmString(const std::string& str)
{
	DefaultErrorHandler handler(false, false);
	return parsePmmString(str, handler);
}

};
