#include "mesh.h"
#include "stlReader.h"
#include "stlWriter.h"

Mesh::Mesh() {}

void Mesh::addPoint(const Point& point) {
    points.push_back(point);
}

void Mesh::addFace(const Face& face) {
    faces.push_back(face);
}

const std::vector<Point>& Mesh::getPoints() const {
    return points;
}

const std::vector<Face>& Mesh::getFaces() const {
    return faces;
}

void Mesh::clear() {
    points.clear();
    faces.clear();
}
