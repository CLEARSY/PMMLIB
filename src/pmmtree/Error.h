/******************************* CLEARSY **************************************
This file is part of PMMLIB
    Copyright © CLEARSY 2008-2020 (contact@clearsy.com)

    PMMLIB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; GNU General Public License version 3
    of the License

    PMMLIB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PMMLIB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/
#ifndef ERROR_H_
#define ERROR_H_

#include <string>

namespace theory
{
/**
 * Base class for Bart error system. Error instances are meant to be throw
 * to indicate errors in the program (such as an incorrect parameter to a method
 * or a broken invariant).
 *
 * To indicate exceptional behaviour (i.e. an error that can occur during the normal
 * execution of the program, such as a file that cannot be opened), the Exception
 * class should be used instead.
 */
class Error  {
	std::string message;

public:
	/**
	 * Creates a new Error with the given description of the error.
	 * The description should be human-readable and understandable by
	 * a developer of the program.
	 *
	 * @param message a human-readable description of the error.
	 */
	Error(const std::string &message);
	/**
	 * Creates a new error that is a copy of the given error.
	 * @param err the Error that should be copied
	 */
	Error(const Error& err);
	virtual ~Error();

	/**
	 * Copies the given error.
	 *
	 * @param err the Error to copy
	 * @return the current Error
	 */
	Error& operator = (const Error& err);

	/**
	 * Returns the description of the error.
	 *
	 * @return the description of the error
	 */
	std::string &getMessage();

};
};

#endif /*ERROR_H_*/
