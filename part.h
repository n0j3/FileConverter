#ifndef PART_H
#define PART_H

#include <vector>
#include <string>

struct Point {
    float x = 0, y = 0, z = 0;
};

struct Face {
    Point facet;
    Point vertices[3]; // Triangle face with 3 vertices
    u_int16_t attribute = 0;

};


class Part {
public:
    Part();

    void addPoint(const Point& point);
    void addFace(const Face& face);
    void clear();
    void display();
    const std::vector<Point>& getPoints() const;
    const std::vector<Face>& getFaces() const;

    std::vector<Point> points;
    std::vector<Face> faces;

private:
};

#endif // PART_H
