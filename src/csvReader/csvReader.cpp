// csvReader.cpp : Defines the entry point for the console application.
//
/**
 * @file
 * @brief Main entry point
 *
 * This file defines the entry point for the console application.
 */
#include "stdafx.h"
#include <fstream>
#include <libcsv\csv.h>
#include <list>
using std::list;
using std::string;

/**
 * @brief Information of parsed records
 */
struct ParseInfo
{
    /**
     * @brief List of completely parsed records
     */
    list< list< string > > records;
    /**
     * @brief Current active, partially parsed record
     */
    list< string > lastRec;
};

namespace
{
    /**
     * @brief Appends a field to the current active record
     *
     * @param[in] txt        field to add
     * @param[in] txtLen     field length, in bytes
     * @param     parsedRecs parsed information
     */
    void AddField(void* txt, size_t txtLen, void* parsedRecs)
    {

        ((ParseInfo*)parsedRecs)->lastRec.push_back((char*)txt);

    }

    /**
     * @brief Appends a record to the record list
     *
     * The current active record is reset for the next record reading
     * operation.
     *
     * @param[in] delim      record delimiter
     * @param     parsedRecs parsed information
     */
    void AddRecord(int delim, void* parsedRecs)
    {
        ParseInfo* const recStore = (ParseInfo*)parsedRecs;

        recStore->records.push_back(recStore->lastRec);
        recStore->lastRec.clear();

    }
}

/**
 * @brief Executes the program
 *
 * @param[in] argc number of command-line arguments
 * @param[in] argv command-line arguments
 * @return         program exit code
 */
int _tmain(int argc, _TCHAR* argv[])
{
    using std::ifstream;
    static const std::size_t bufSize = 1024;
    char buf[bufSize];
    ifstream csvFile(argv[1], ifstream::binary);
    csv_parser parser;
    ParseInfo records;

    csv_init(&parser, CSV_APPEND_NULL);
    csv_fini(&parser, AddField, AddRecord, &records);

    while (csvFile.read(buf, bufSize)) csv_parse(
        &parser, buf, size_t(csvFile.gcount()), AddField, AddRecord, &records);

    csv_free(&parser);
    csvFile.close();
    return 0;
}

