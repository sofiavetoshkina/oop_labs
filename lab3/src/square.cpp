#include <iostream>
#include "square.h"

Square::Square(const Vertex& vertex, double width) : vertex(vertex), width(width) {} 

Square::Square(const Square& sq) : vertex(sq.vertex), width(sq.width) {} 

Square::Square(Square&& sq) noexcept : vertex(std::move(sq.vertex)), width(sq.width) {}

Square& Square::operator=(const Square& sq) {
    if (this != &sq) {
        vertex = sq.vertex;
        width = sq.width;
    }
    return *this;
}

Square& Square::operator=(Square&& sq) noexcept {
    if (this != &sq) {
        vertex = std::move(sq.vertex);
        width = sq.width;
    }
    return *this;
}
    
bool Square::operator==(const Square& other) const {
    return vertex == other.vertex && width == other.width;
}

Square::operator double() const {
    return width * width;
}

Vertex Square::getCenter() const {
    return Vertex(vertex.getX() + (width / 2), vertex.getY() - (width / 2));
}

std::ostream& operator<<(std::ostream& os, const Square& sq) {
    os << "левая верхняя точка: " << sq.vertex << ", ширина: " << sq.width;
    return os;
}

std::istream& operator>>(std::istream& is, Square& sq) {
    is >> sq.vertex >> sq.width;
    return is;
}

