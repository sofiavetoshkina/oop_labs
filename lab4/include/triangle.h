#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "figure.h"


namespace { const size_t TR_POINTS = 3; }

template <typename T>
class Triangle : public Figure<T>
{
public:
    Triangle() = default; // Конструктор по умолчанию
    Triangle(const std::vector<Vertex<T>>& vertices) { // Конструктор(принимает три точки)
        if (vertices.size() != TR_POINTS) {
            throw std::invalid_argument("Треугольник должен быть инициализирован 3 точками.");
        }
        if (!isTriangle(vertices)) {
            throw std::invalid_argument("Приведенные точки не образуют треугольник.");
        }
        this->vertices = vertices;
    }

    double distance(const Vertex<T>& v1, const Vertex<T>& v2) const { // Вычисление расстояния между точками
        return std::sqrt((v1.getX() - v2.getX()) * (v1.getX() - v2.getX()) + (v1.getY() - v2.getY()) * (v1.getY() - v2.getY()));
    }

    bool isTriangle(const std::vector<Vertex<T>>& vertices) const { // Проверка на существование треугольника
        double s1 = distance(vertices[0], vertices[1]);
        double s2 = distance(vertices[1], vertices[2]);
        double s3 = distance(vertices[2], vertices[0]);
        return ((s1 + s2) > s3 && (s1 + s3) > s2 && (s2 + s3) > s1);
    }

    Triangle(const Triangle<T>& triangle) : vertices(triangle.vertices) {} // Конструктор копирования
    
    Triangle(Triangle<T>&& triangle) noexcept : vertices(std::move(triangle.vertices)) {} // Конструктор перемещения

    Triangle<T>& operator=(const Triangle<T>& other) { // Оператор копирования
        vertices = other.vertices;
        return *this;
    }

    Triangle<T>& operator=(Triangle<T>&& other) noexcept { // Оператор перемещения
        vertices = std::move(other.vertices);
        return *this;
    }

    bool operator==(const Triangle<T>& other) const { // Сравнение на равенство
        for (int i = 0, j = 0; j < TR_POINTS; ++j) {
            if (i == TR_POINTS) return true;
            else if (vertices[i] == other.vertices[j]) {
                ++i;
                j = -1;
                }
        }
        return false;
    }

    operator double() const override { // Переопределение double для получения площади
        double s1 = distance(vertices[0], vertices[1]);
        double s2 = distance(vertices[1], vertices[2]);
        double s3 = distance(vertices[2], vertices[0]);
        double pp = (s1 + s2 + s3) / 2;  
        return std::sqrt(pp * (pp - s1) * (pp - s2) * (pp - s3));
    }

    Vertex<T> getCenter() const override { // Получение геометрического центра
        T x = (vertices[0].getX() + vertices[1].getX() + vertices[2].getX()) / 3;
        T y = (vertices[0].getY() + vertices[1].getY() + vertices[2].getY()) / 3;
        return Vertex(x, y);
    }

    template <typename V>
    friend std::ostream& operator<<(std::ostream& os, const Triangle<V>& triangle);

    template <typename V>
    friend std::istream& operator>>(std::istream& is, Triangle<V>& triangle);

private:
    std::vector<Vertex<T>> vertices;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Triangle<T>& triangle) {
    for (const auto& vertex : triangle.vertices) {
        os << vertex << " ";
    }
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Triangle<T>& triangle) {
    std::vector<Vertex<T>> verices(TR_POINTS);
    for (int i = 0; i < TR_POINTS; ++i) {
        is >> verices[i];
    }
    triangle = Triangle<T>(verices);
    return is;
}