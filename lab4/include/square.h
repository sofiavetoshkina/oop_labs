#pragma once

#include <iostream>
#include "figure.h"

template <typename T>
class Square : public Figure<T>
{
public:
    Square() = default; // Конструктор по умолчанию
    Square(const Vertex<T>& vertex, T width) : vertex(vertex), width(width) {}  // Конструктор: принимает точку(левую верхнюю) и ширину 

    Square(const Square<T>& sq) : vertex(sq.vertex), width(sq.width) {}  // Конструктор копирования
    Square(Square<T>&& sq) noexcept : vertex(std::move(sq.vertex)), width(std::move(sq.width)) {}  // Конструктор перемещения

    Square<T>& operator=(const Square<T>& sq) { // Оператор копирования
        if (this != &sq) {
            vertex = sq.vertex;
            width = sq.width;
        }
        return *this;
    }
    Square<T>& operator=(Square<T>&& sq) noexcept { // Оператор перемещения
        if (this != &sq) {
            vertex = std::move(sq.vertex);
            width = std::move(sq.width);
        }
        return *this;
    }

    bool operator==(const Square<T>& other) const { // Сравнение на равенство
        return vertex == other.vertex && width == other.width;
    }

    operator double() const override { // Переопределение double для получения площади
        return width * width;
    }

    Vertex<T> getCenter() const override { // Получение геометрического центра
        return Vertex(vertex.getX() + (width / 2), vertex.getY() - (width / 2));
    }

    template <typename V>
    friend std::ostream& operator<<(std::ostream& os, const Square<V>& sq);
    template <typename V>
    friend std::istream& operator>>(std::istream& is, Square<V>& sq);

private:
    Vertex<T> vertex;
    T width; 
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Square<T>& sq) {
    os << "левая верхняя точка: " << sq.vertex << ", ширина: " << sq.width;
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Square<T>& sq) {
    is >> sq.vertex >> sq.width;
    return is;
}

