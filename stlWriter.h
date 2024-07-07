#ifndef STL_WRITER_H
#define STL_WRITER_H

#include <string>
#include "mesh.h"

class STL_Writer {
public:
    STL_Writer();
    bool write(const Mesh &mesh, const std::string &filePath);
    bool isCorrupt() const;

private:
    bool corrupt;

    bool isValidSTLFile(const std::string &filePath);
};

#endif // STL_WRITER_H
