/**
 * @file
 * @brief CSV file utility library
 *
 * This file contains utility functions for reading csv files.
 */
#ifndef CSV_H
#define CSV_H
#include <boost\algorithm\string\regex.hpp>
#include <fstream>

/**
 * @brief Utilities for processing csv files
 */
namespace CsvUtils
{
    /**
     * @brief Reads records in a csv stream
     *
     * @tparam     T       output record iterator, where a record is represented
     *                     by a field vector
     * @param[in]  csvSrc  csv source stream
     * @param[out] records output iterator to a record, where a single record is
     *                     represented by a field vector
     * @return             iterator past the last record
     */
    template < class T >
    T ReadCsv(std::istream& csvSrc, T records)
    {
        using std::string;
        string line;
        std::vector< string > recParts;
        static const char sep[] = ",";

        while (std::getline(csvSrc, line))
        {

            boost::split_regex(recParts, line, boost::regex(sep));
            *(records++) = recParts;

        }

        return records;

    }

    /**
     * @brief Reads records in a csv file
     *
     * This function opens the given csv file, parses the records in it, and
     * then closes it.
     *
     * @tparam     T       output record iterator, where a record is represented
     *                     by a field vector
     * @param[in]  csvName csv file name
     * @param[out] records output iterator to a record, where a single record is
     *                     represented by a field vector
     * @return             iterator past the last record
     */
    template < class T >
    T ReadCsvFile(const _TCHAR csvName[], T records)
    {
        std::ifstream csvFile(csvName);

        records = ReadCsv(csvFile, records);
        csvFile.close();
        return records;

    }
}
#endif
