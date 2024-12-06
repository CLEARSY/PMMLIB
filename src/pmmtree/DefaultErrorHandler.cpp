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
#include <iostream>
#include <string>
#include "DefaultErrorHandler.h"

namespace theory
{
DefaultErrorHandler::DefaultErrorHandler(bool print_errors, bool print_warnings)
	: errorCount(0), warningCount(0), printErrors(print_errors), printWarnings(print_warnings)
{
}

DefaultErrorHandler::~DefaultErrorHandler()
{
}

void
DefaultErrorHandler::error(const std::string& description,
		const std::string& file_name,
		int line, int column)
{
	++errorCount;

	if(printErrors)
	{
		bool hasnewline = (int)description.find('\n', 0) != -1;

		std::cout << file_name << ":";

		if(line != UNDEFINED)
		{
			std::cout << line << ":";
		}
		if(column != UNDEFINED)
		{
			std::cout << column << ":";
		}
		std::cout << "error: " << description;
		if(!hasnewline)
		{
			std::cout << std::endl;
		}
	}
}

void
DefaultErrorHandler::warning(const std::string& description, const std::string& file_name, int line, int column)
{
	++warningCount;

	if(printWarnings)
	{
		bool hasnewline = (int)description.find('\n', 0) != -1;

		std::cout  << file_name << ":";
		if(line != UNDEFINED)
		{
			std::cout << line << ":";
		}
		if(column != UNDEFINED)
		{
			std::cout << column << ":";
		}
		std::cout << "warning: " << description;
		if(!hasnewline)
		{
			std::cout << std::endl;
		}
	}
}
bool
DefaultErrorHandler::hasErrors() const
{
	return errorCount != 0;
}

bool
DefaultErrorHandler::hasWarnings() const
{
	return warningCount != 0;
}

void
DefaultErrorHandler::reset()
{
	errorCount = 0;
	warningCount = 0;
}

};
