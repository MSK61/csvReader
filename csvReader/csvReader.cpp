// csvReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "csv.h"

int _tmain(int argc, _TCHAR* argv[])
{
    std::list< std::vector< std::string > > records;

    ReadCsvFile(argv[1], std::back_inserter(records));
	return 0;
}

