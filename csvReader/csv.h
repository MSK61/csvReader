#ifndef CSV_H
#define CSV_H
#include <boost\algorithm\string\regex.hpp>
#include <fstream>

namespace CvsUtils
{
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
