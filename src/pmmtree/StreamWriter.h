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
#ifndef STREAMWRITER_H_
#define STREAMWRITER_H_
#include <iostream>
#include <string>
#include "NodeWriter.h"

namespace theory
{
/**
 * An implementation of NodeWriter that writes to a standard
 * output stream
 */
class StreamWriter : public NodeWriter
{
public:
        StreamWriter(const std::string& file_name);
        StreamWriter(std::ostream *o);
	virtual ~StreamWriter();

	void newLine();
	void write(const std::string&);

	void setIndentation(const std::string&);

        static void setDefaultSingleLine(bool single_line) { defaultSingleLine = single_line; }


        /**
         * Return the stream on which the data is written
         *
         * @return the stream on which data is written
         */
        std::ostream& stream() { return *output; }
private:
	void writeIndent();


	std::ostream *output;
	std::string indent;
        bool deleteStream;

        static bool defaultSingleLine;
};
};

#endif /*STREAMWRITER_H_*/
