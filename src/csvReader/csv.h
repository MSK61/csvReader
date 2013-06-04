#ifndef CSV_H
#define CSV_H
#include <boost\algorithm\string\regex.hpp>
#include <fstream>

/**
  * @brief Utilities for processing csv files
  */
namespace CvsUtils
{
    /**
      * @brief Appends a field to the current active record
      *
      * This function opens the given csv file, parses the records in it, and
      * the closes it.
      *
      * @tparam    T        output record iterator, where a record is
      *                     represented by a field vector
      * @param[in]  csvName csv file name
      * @param[out] records output iterator to a record, where a single record
      *                     is represented by a field vector
      */
    template < class T >
    void ReadCsvFile(const _TCHAR csvName[], T records)
    {
        using std::string;
        std::ifstream csvFile(csvName);
        string line;
        std::vector< string > recParts;
        static const char sep[] = ",";

        while (std::getline(csvFile, line))
        {

            boost::split_regex(recParts, line, boost::regex(sep));
            *(records++) = recParts;

        }

        csvFile.close();

    }
}
#endif
