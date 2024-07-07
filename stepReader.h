#ifndef STEP_READER_H
#define STEP_READER_H

#include <string>
#include <vector>
#include "mesh.h"

class STEP_Reader {
public:
    STEP_Reader();
    bool read(const std::string &filePath);
    bool isCorrupt() const;

    const std::vector<Point>& getPointCloud() const;

private:
    std::vector<Point> pointCloud;
    bool corrupt;

    bool isValidSTEPFile(const std::string &filePath);
};

#endif // STEP_READER_H
