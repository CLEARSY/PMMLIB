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
#include "StreamWriter.h"
#include <fstream>

namespace theory
{
    bool StreamWriter::defaultSingleLine = true;

    StreamWriter::StreamWriter(const std::string& file_name)
        : NodeWriter(defaultSingleLine), output(0), indent("  "), deleteStream(true)
    {
        output = new std::ofstream(file_name.c_str());
    }

    StreamWriter::StreamWriter(std::ostream *o)
        : NodeWriter(defaultSingleLine), output(o), indent("  "), deleteStream(false)
    {
    }

    StreamWriter::~StreamWriter()
    {
        if(deleteStream)
        {
            output->flush();
            delete output;
            output = 0;
        }
    }

    void StreamWriter::newLine()
    {
        *output << std::endl;
        writeIndent();
    }

    void StreamWriter::write(const std::string& str)
    {
        *output << str;
    }

    void
            StreamWriter::setIndentation(const std::string& new_indentation)
    {
        indent = new_indentation;
    }

    void
            StreamWriter::writeIndent()
    {
        int indent_level = getLevel();
        for(int i=0; i<indent_level; ++i)
        {
            *output << indent;
        }
    }
};
