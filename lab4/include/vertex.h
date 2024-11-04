#pragma once

#include <iostream>
#include <concepts>

// Концепт для проверки, что тип T является скалярным
template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Vertex
{
public:
    Vertex() : _x(0), _y(0) {} // Конструктор по умолчанию
    Vertex(T x_in, T y_in) : _x(x_in), _y(y_in) {} // Конструктор с координатами (x, y) вершины

    Vertex(const Vertex<T>& other) : _x(other._x), _y(other._y) {} // Конструктор копирования
    Vertex(Vertex<T>&& other) noexcept : _x(std::move(other._x)), _y(std::move(other._y)) {} // Конструктор перемещения

    T getX() const { // Метод для получения значения x
        return _x;
    }
    T getY() const { // Метод для получения значения y
        return _y;
    }

    Vertex<T>& operator=(const Vertex<T>& other) { // Оператор копирования
        if (this != &other) {
            _x = other._x;
            _y = other._y;
        }
        return *this;
    }
    Vertex<T>& operator=(Vertex<T>&& other) noexcept { // Оператор перемещения
        if (this != &other) {
            _x = std::move(other._x);
            _y = std::move(other._y);
        }
        return *this;
    }

    Vertex<T> operator+(const Vertex<T>& other) const { // Оператор сложения координат двух вершин
        return Vertex(_x + other._x, _y + other._y);
    }
    Vertex<T> operator-(const Vertex<T>& other) const { // Оператор вычитания координат двух вершин
        return Vertex(_x - other._x, _y - other._y);
    }

    Vertex<T>& operator+=(const Vertex<T>& other) {
        _x += other._x;
        _y += other._y;
        return *this;
    }
    Vertex<T>& operator-=(const Vertex<T>& other) {
        _x -= other._x;
        _y -= other._y;
        return *this;       
    }

    bool operator==(const Vertex<T>& other) const { // Оператор проверки на равенство
        return (_x == other._x && _y == other._y);
    }

    template <Scalar V>
    friend std::ostream& operator<<(std::ostream& os, const Vertex<V>& vertex);

    template <Scalar V>
    friend std::istream& operator>>(std::istream& is, Vertex<V>& vertex);

private:
    T _x;
    T _y;
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex) {
    os << "(" << vertex._x << ", " << vertex._y << ")";
    return os;
}
    
template <Scalar T>
std::istream& operator>>(std::istream& is, Vertex<T>& vertex) {
    is >> vertex._x >> vertex._y;
    return is;
}