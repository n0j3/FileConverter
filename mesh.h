#ifndef MESH_H
#define MESH_H

#include <vector>

// Point structure
struct Point {
    float x, y, z;
};

// Mesh structure
struct Mesh {
    std::vector<Point> vertices;
    std::vector<std::vector<int>> faces;
};

#endif // MESH_H
