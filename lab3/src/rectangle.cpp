#include <iostream>
#include "rectangle.h"

Rectangle::Rectangle(const Vertex& vertex, double width, double height) : vertex(vertex), width(width), height(height) {} 

Rectangle::Rectangle(const Rectangle& r) : vertex(r.vertex), width(r.width), height(r.height) {} 

Rectangle::Rectangle(Rectangle&& r) noexcept : vertex(std::move(r.vertex)), width(r.width), height(r.height) {}

Rectangle& Rectangle::operator=(const Rectangle& r) {
    if (this != &r) {
        vertex = r.vertex;
        width = r.width;
        height = r.height;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& r) noexcept {
    if (this != &r) {
        vertex = std::move(r.vertex);
        width = r.width;
        height = r.height;
    }
    return *this;
}
    
bool Rectangle::operator==(const Rectangle& other) const {
    return vertex == other.vertex && width == other.width && height == other.height;
}

Rectangle::operator double() const {
    return width * height;
}

Vertex Rectangle::getCenter() const {
    return Vertex(vertex.getX() + (width / 2), vertex.getY() - (height / 2));
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
    os << "левая верхняя точка: " << r.vertex << ", ширина: " << r.width << ", высота: " << r.height;
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& r) {
    is >> r.vertex >> r.width >> r.height;
    return is;
}

