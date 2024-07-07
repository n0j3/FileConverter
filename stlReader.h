#ifndef STL_READER_H
#define STL_READER_H

#include <string>
#include <vector>
#include "mesh.h"

class STL_Reader {
public:
    STL_Reader();
    bool read(const std::string &filePath);
    bool isCorrupt() const;

    const std::vector<Point>& getPointCloud() const;

private:
    std::vector<Point> pointCloud;
    bool corrupt;

    bool isValidSTLFile(const std::string &filePath);
};

#endif // STL_READER_H
