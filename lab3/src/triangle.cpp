#include <stdexcept>
#include <cmath>
#include <vector>
#include "triangle.h"

namespace { const size_t TR_POINTS = 3; }

double Triangle::distance(const Vertex& v1, const Vertex& v2) const {
    return std::sqrt((v1.getX() - v2.getX()) * (v1.getX() - v2.getX()) + (v1.getY() - v2.getY()) * (v1.getY() - v2.getY()));
}

bool Triangle::isTriangle(const std::vector<Vertex>& vertices) const {
    double s1 = distance(vertices[0], vertices[1]);
    double s2 = distance(vertices[1], vertices[2]);
    double s3 = distance(vertices[2], vertices[0]);
    return ((s1 + s2) > s3 && (s1 + s3) > s2 && (s2 + s3) > s1);
}

Triangle::Triangle(const std::vector<Vertex>& vertices) {
    if (vertices.size() != TR_POINTS) {
        throw std::invalid_argument("Треугольник должен быть инициализирован 3 точками.");
    }
    if (!isTriangle(vertices)) {
        throw std::invalid_argument("Приведенные точки не образуют треугольник.");
    }
    this->vertices = vertices;
}

Triangle::Triangle(const Triangle& triangle) : vertices(triangle.vertices) {}

Triangle::Triangle(Triangle&& triangle) noexcept : vertices(std::move(triangle.vertices)) {}


Triangle& Triangle::operator=(const Triangle& other) {
    vertices = other.vertices;
    return *this;
}


Triangle& Triangle::operator=(Triangle&& other) noexcept {
    vertices = std::move(other.vertices);
    return *this;
}

bool Triangle::operator==(const Triangle& other) const {
	for (int i = 0, j = 0; j < TR_POINTS; ++j) {
	    if (i == TR_POINTS) return true;
		else if (vertices[i] == other.vertices[j]) {
			++i;
			j = -1;
		}
	}
	return false;
}

Vertex Triangle::getCenter() const {
    double x = (vertices[0].getX() + vertices[1].getX() + vertices[2].getX()) / 3;
    double y = (vertices[0].getY() + vertices[1].getY() + vertices[2].getY()) / 3;
    return Vertex(x, y);
}

Triangle::operator double() const {
    double s1 = distance(vertices[0], vertices[1]);
    double s2 = distance(vertices[1], vertices[2]);
    double s3 = distance(vertices[2], vertices[0]);
    double pp = (s1 + s2 + s3) / 2;  
    return std::sqrt(pp * (pp - s1) * (pp - s2) * (pp - s3));
}

std::ostream& operator<<(std::ostream &os, const Triangle& triangle) {
    for (const auto& vertex : triangle.vertices) {
        os << vertex << " ";
    }
    return os;
}

std::istream& operator>>(std::istream &is, Triangle& triangle) {
    std::vector<Vertex> verices(TR_POINTS);
    for (int i = 0; i < TR_POINTS; ++i) {
        is >> verices[i];
    }
    triangle = Triangle(verices);
    return is;
}