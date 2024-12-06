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
#ifndef DEFAULTERRORHANDLER_H_
#define DEFAULTERRORHANDLER_H_

#include "ErrorHandler.h"
namespace theory
{
/**
 * A default error handler, that displays errors on the standard output
 * in a format similar to gcc's error output
 */
class DefaultErrorHandler : public ErrorHandler
{
private:
	int errorCount;
	int warningCount;
	bool printErrors;
	bool printWarnings;

public:
	DefaultErrorHandler(bool print_errors = true, bool print_warnings = true);
	virtual ~DefaultErrorHandler();

	void error(const std::string& description, const std::string& file_name, int line, int column);
	void warning(const std::string& description, const std::string& file_name, int line, int column);

	/**
	 * Indicates whether errors and warnings should be printed
	 *
	 * @param errors indicates whether the errors should be displayed
	 * @param warnings indicats whether the warning should be displayed
	 */
	void printMessages(bool errors, bool warnings);

	bool hasErrors() const;
	bool hasWarnings() const;
	void reset();
};
};
#endif /*DEFAULTERRORHANDLER_H_*/
