#ifndef STEP_READER_H
#define STEP_READER_H

#include <string>
#include <vector>
#include "mesh.h"

class STEP_Reader {
public:
    STEP_Reader();

    const Mesh& getMesh() const;
    const std::vector<Point>& getPointCloud() const;

    bool isCorrupt() const;
    bool read(const std::string &filePath);

private:
    bool isValidSTEPFile(const std::string &filePath);

    const Mesh mesh;
    const std::vector<Point> pointCloud;

    bool corrupt;
};

#endif // STEP_READER_H
