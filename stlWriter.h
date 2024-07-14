#ifndef STL_WRITER_H
#define STL_WRITER_H

#include <string>
#include <vector>
#include "part.h"


class STL_Writer {
public:
    STL_Writer();

    bool isCorrupt() const;
    bool writeSTL(const Part &part, const std::string &filePath, const bool &binary = true);

private:
    bool isValidSTLFilePath(const std::string &filePath);
    bool writeBinarySTL(const std::string &filePath, const Part &Part);
    bool writeASCIISTL(const std::string &filePath, const Part &Part);

    bool binary;
    bool corrupt;
};

#endif // STL_WRITER_H
