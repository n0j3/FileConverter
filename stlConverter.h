#ifndef STL_CONVERTER_H
#define STL_CONVERTER_H

#include <vector>
#include "mesh.h"

class STL_Converter {
public:
    STL_Converter();
    Mesh convertToMesh(const std::vector<Point> &pointCloud);
    std::vector<Point> convertToPointCloud(const Mesh &mesh);
};

#endif // STL_CONVERTER_H
