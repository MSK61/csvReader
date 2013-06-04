// csvReader.cpp : Defines the entry point for the console application.
//
/**
 * @file
 * @brief Main entry point
 *
 * This file defines the entry point for the console application.
 */

#include "stdafx.h"
#include "csv.h"

/**
* @brief Executes the program
*
* @param[in] argc number of command-line arguments
* @param[in] argv command-line arguments
*/
int _tmain(int argc, _TCHAR* argv[])
{
    std::list< std::vector< std::string > > records;

    CvsUtils::ReadCsvFile(argv[1], std::back_inserter(records));
    return 0;
}

