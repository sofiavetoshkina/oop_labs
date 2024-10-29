#include <iostream>
#include "vertex.h"

Vertex::Vertex() : _x(0.0), _y(0.0) {}
Vertex::Vertex(double x_in, double y_in) : _x(x_in), _y(y_in) {}

Vertex::Vertex(const Vertex& other) : _x(other._x), _y(other._y) {}

Vertex::Vertex(Vertex&& other) noexcept : _x(other._x), _y(other._y) {
    other._x = 0.0;
    other._y = 0.0;
}

double Vertex::getX() const {
    return _x;
}

double Vertex::getY() const {
    return _y;
}

Vertex& Vertex::operator=(const Vertex& other) {
    if (this != &other){
        _x = other._x;
        _y = other._y;
    }
    return *this;
}

Vertex& Vertex::operator=(Vertex &&other) noexcept {
    if (this != &other){
        _x = other._x;
        _y = other._y;
        other._x = 0.0;
        other._y = 0.0;
    }
    return *this;
}

Vertex Vertex::operator+(const Vertex& other) const {
	return Vertex(_x + other._x, _y + other._y);
}

Vertex Vertex::operator-(const Vertex& other) const {
	return Vertex(_x - other._x, _y - other._y);
}

Vertex& Vertex::operator+=(const Vertex& other) {
	_x += other._x;
	_y += other._y;
	return *this;
}

Vertex& Vertex::operator-=(const Vertex& other) {
	_x -= other._x;
	_y -= other._y;
	return *this;
}

bool Vertex::operator==(const Vertex& other) const {
	return (_x == other._x && _y == other._y);
}

std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
	os << "(" << vertex._x << ", " << vertex._y << ")";
	return os;
}

std::istream& operator>>(std::istream& is, Vertex& vertex) {
	is >> vertex._x >> vertex._y;
	return is;
}
