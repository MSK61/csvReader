// csvReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <libcsv\csv.h>
#include <list>
using std::list;
using std::string;

struct ParseInfo
{
    list< list< string > > records;
    list< string > lastRec;
};

namespace
{
    void AddField(void* txt, size_t txtLen, void* parsedRecs)
    {

        ((ParseInfo*)parsedRecs)->lastRec.push_back((char*)txt);

    }

    void AddRecord(int delim, void* parsedRecs)
    {
        ParseInfo* const recStore = (ParseInfo*)parsedRecs;

        recStore->records.push_back(recStore->lastRec);
        recStore->lastRec.clear();

    }
}

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

    while(csvFile.read(buf, bufSize)) csv_parse(
        &parser, buf, size_t(csvFile.gcount()), AddField, AddRecord, &records);

    csv_free(&parser);
    csvFile.close();
    return 0;
}

