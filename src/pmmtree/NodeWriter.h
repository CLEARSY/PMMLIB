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
#ifndef NODEWRITER_H_
#define NODEWRITER_H_
#include <string>

namespace theory
{
/**
 * Class that is used to write nodes
 */
class NodeWriter
{
public:
        NodeWriter(bool single_line = true);
	virtual ~NodeWriter();

        virtual void increaseLevel();
        virtual void decreaseLevel();
        virtual int getLevel() const;

	virtual void newLine() = 0;

	virtual void increaseAndNewLine();
	virtual void decreaseAndNewLine();

	virtual void write(const std::string&) = 0;

        virtual void setSingleLine(bool single_line);
        virtual void setSingleLineLevel(int level);

        virtual bool singleLine() const;

private:
        int level;
        /*!
         * Level after which the formulas are written on a single line.
         * 0 means that the formulas are always written on a single line,
         * -1 indicate that the formulas are never written on a single line, and
         * another value indicate that formulas at a level larger than singleLineLevel
         * will be written on a single line, but lower levels will be written on several
         * lines.
         */
        int singleLineLevel;
};
};

#endif /*NODEWRITER_H_*/
