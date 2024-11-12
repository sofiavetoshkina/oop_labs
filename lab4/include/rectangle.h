#pragma once

#include <iostream>
#include "figure.h"

template <typename T>
class Rectangle : public Figure<T>
{
public:
    Rectangle() = default; // Конструктор по умолчанию
    Rectangle(const Vertex<T>& vertex, T width, T height) : vertex(vertex), width(width), height(height) {} // Конструктор: принимает точку(левую верхнюю), ширину, высоту

    Rectangle(const Rectangle<T>& r) : vertex(r.vertex), width(r.width), height(r.height) {} // Конструктор копирования
    Rectangle(Rectangle<T>&& r) noexcept : vertex(std::move(r.vertex)), width(std::move(r.width)), height(std::move(r.height)) {} // Конструктор перемещения

    Rectangle<T>& operator=(const Rectangle<T>& r) { // Оператор копирования
        if (this != &r) {
            vertex = r.vertex;
            width = r.width;
            height = r.height;
        }
        return *this;
    }

    Rectangle<T>& operator=(Rectangle<T>&& r) noexcept { // Оператор перемещения
        if (this != &r) {
            vertex = std::move(r.vertex);
            width = std::move(r.width);
            height = std::move(r.height);
        }
        return *this;
    }

    bool operator==(const Rectangle<T>& other) const { // Сравнение на равенство
        return vertex == other.vertex && width == other.width && height == other.height;
    }

    operator double() const override { // Переопределение double для получения площади
        return width * height;
    }   

    Vertex<T> getCenter() const override { // Получение геометрического центра
        return Vertex(vertex.getX() + (width / 2), vertex.getY() - (height / 2));
    }

    template <typename V>
    friend std::ostream& operator<<(std::ostream& os, const Rectangle<V>& r);
    template <typename V>
    friend std::istream& operator>>(std::istream& is, Rectangle<V>& r);

private:
    Vertex<T> vertex;
    T width; 
    T height;
};

    
template <typename T>
std::ostream& operator<<(std::ostream& os, const Rectangle<T>& r) {
    os << "левая верхняя точка: " << r.vertex << ", ширина: " << r.width << ", высота: " << r.height;
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Rectangle<T>& r) {
    is >> r.vertex >> r.width >> r.height;
    return is;
}
