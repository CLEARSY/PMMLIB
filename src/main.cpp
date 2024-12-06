/******************************* CLEARSY **************************************
This file is part of PMMLIB
    Copyright  © CLEARSY 2008-2020 (contact@clearsy.com)

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
#include <common.h>
#include <pmmparser/PmmParser.h>
#include <pmmtree/BNode.h>
#include <pmmparser/PmmFile.h>
#include <pmmtree/DefaultErrorHandler.h>
#include <pmmtree/StreamWriter.h>

using namespace theory;

int
main(int argc, char **argv)
{
	if(argc == 1)
	{
		std::cout << "Specify one or more pmm files" << std::endl;
	}
	else
	{
		for(int i=1; i<argc; ++i)
		{
			DefaultErrorHandler handler;
			std::cout << "Loading " << argv[i] << std::endl;
			BNode *pmm = PmmParser::parsePmmFile(argv[i], handler);
			if(pmm)
			{
//				StreamWriter s(&std::cout);
//				pmm->writeTo(s);
			}
			else
			{
				std::cout << "Error" << std::endl;
			}

		}
	}
	return 0;
}
