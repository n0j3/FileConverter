#ifndef STEP_CONVERTER_H
#define STEP_CONVERTER_H

#include <vector>
#include "mesh.h"

class STEP_Converter {
public:
    STEP_Converter();
    Mesh convertToMesh(const std::vector<Point> &pointCloud);
    std::vector<Point> convertToPointCloud(const Mesh &mesh);
};

#endif // STEP_CONVERTER_H
