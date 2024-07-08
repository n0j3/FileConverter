#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

struct Point {
    float x, y, z;
};

struct Face {
    Point facet;
    Point vertices[3]; // Triangle face with 3 vertices
};


class Mesh {
public:
    Mesh();

    void addPoint(const Point& point);
    void addFace(const Face& face);
    void clear();
    const std::vector<Point>& getPoints() const;
    const std::vector<Face>& getFaces() const;

    std::vector<Point> points;
    std::vector<Face> faces;

private:
};

#endif // MESH_H
