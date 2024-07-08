#ifndef STL_WRITER_H
#define STL_WRITER_H

#include <string>
#include <vector>
#include "mesh.h"


class STL_Writer {
public:
    STL_Writer();

    bool writeSTL(const Mesh &mesh, const std::string &filePath, const bool &binary = true);
    bool isCorrupt() const;

private:
    bool isValidSTLFilePath(const std::string &filePath);
    bool writeBinarySTL(const std::string &filePath, const Mesh &mesh);
    bool writeASCIISTL(const std::string &filePath, const Mesh &mesh);

    bool corrupt;
};

#endif // STL_WRITER_H
