#pragma once

#include <iostream>
#include "figure.h"

class Rectangle : public Figure
{
public:
    Rectangle() = default; // Конструктор по умолчанию
    Rectangle(const Vertex& vertex, double width, double height); // Конструктор: принимает точку(левую верхнюю), ширину, высоту

    Rectangle(const Rectangle& r); // Конструктор копирования
    Rectangle(Rectangle&& r) noexcept; // Конструктор перемещения

    Rectangle& operator=(const Rectangle& r); // Оператор копирования
    Rectangle& operator=(Rectangle&& r) noexcept; // Оператор перемещения
    
    bool operator==(const Rectangle& other) const; // Сравнение на равенство

    operator double() const override; // Переопределение double для получения площади
    Vertex getCenter() const override; // Получение геометрического центра

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& r);
    friend std::istream& operator>>(std::istream& is, Rectangle& r);

private:
    Vertex vertex;
    double width; 
    double height;
};
