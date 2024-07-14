#include "part.h"

Part::Part() {}

void Part::addPoint(const Point& point) {
    points.push_back(point);
}

void Part::addFace(const Face& face) {
    faces.push_back(face);
}

void Part::display() {
    //TODO
}

const std::vector<Point>& Part::getPoints() const {
    return points;
}

const std::vector<Face>& Part::getFaces() const {
    return faces;
}

void Part::clear() {
    points.clear();
    faces.clear();
}
