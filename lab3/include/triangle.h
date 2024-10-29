#include <iostream>
#include <vector>
#include "figure.h"

class Triangle : public Figure
{
public:
    Triangle() = default; // Конструктор по умолчанию
    Triangle(const std::vector<Vertex>& vertices); // Конструктор(принимает три точки)

    double distance(const Vertex& v1, const Vertex& v2) const; // Вычисление расстояния между точками
    bool isTriangle(const std::vector<Vertex>& vertices) const; // Проверка на существование треугольника
    
    Triangle(const Triangle& triangle); // Конструктор копирования
    Triangle(Triangle&& triangle) noexcept; // Конструктор перемещения

    Triangle& operator=(const Triangle& triangle); // Оператор копирования
    Triangle& operator=(Triangle&& triangle) noexcept; // Оператор перемещения
    
    bool operator==(const Triangle& other) const; // Сравнение на равенство

    operator double() const override; // Переопределение double для получения площади
    Vertex getCenter() const override; // Получение геометрического центра

    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle);
    friend std::istream& operator>>(std::istream& is, Triangle& triangle);

protected:
    std::vector<Vertex> vertices;
};
