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
#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_
#include <string>
namespace theory
{
/**
 * Base class for handling errors.
 */
class ErrorHandler
{
	/**
	 * Indicates that some errors must be considered as warnings
	 */
	bool warnMode;

public:
	/**
	 * Create a new ErrorHandler
	 */
	ErrorHandler();
	virtual ~ErrorHandler();

	/**
	 * Constant that can be used as line or column to indicate that no information
	 * on the column or the line is available.
	 */
	static const int UNDEFINED = -1;

	/**
	 * Method called to indicate that an error occured.
	 *
	 * @param description a description of the error
	 * @param file_name the name of the file where the error has been
	 *        encountered
	 * @param line the line where the error occured, or UNDEFINED if
	 *        no line can be provided
	 * @param column the column where the error occured or UNDEFINED
	 *        if no column can be provided
	 */
	virtual void error(const std::string& description,
			const std::string& file_name,
			int line = UNDEFINED, int column = UNDEFINED) = 0;

	/**
	 * Method called to indicate that an error occured.
	 *
	 * @param description a description of the error
	 * @param file_name the name of the file where the warning
	 *        occured
	 * @param line the line where the error occured, or UNDEFINED if
	 *        no line can be provided
	 * @param column the column where the error occured or UNDEFINED
	 *        if no column can be provided
	 */
	virtual void warning(const std::string& description,
			const std::string& file_name,
			int line = UNDEFINED, int column = UNDEFINED) = 0;

	/**
	 * Indicates whether an error occured.
	 *
	 * @return true if an error has occured, false otherwise
	 */
	virtual bool hasErrors() const = 0;

	/**
	 * Resets all errors and warnings. After calling reset,
	 * hasErrors and hasWarnings will return false, even if
	 * they were returning true before the call
	 */
	virtual void reset() = 0;

	/**
	 * Indicates warnings have been emitted.
	 *
	 * @return true if a warning has been emitted, false otherwise
	 */
	virtual bool hasWarnings() const = 0;

	void setWarnMode(bool warnMode);
	bool getWarnMode();

};
};
#endif /*ERRORHANDLER_H_*/
