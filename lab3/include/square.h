#pragma once

#include <iostream>
#include "figure.h"

class Square : public Figure
{
public:
    Square() = default; // Конструктор по умолчанию
    Square(const Vertex& vertex, double width); // Конструктор: принимает точку(левую верхнюю) и ширину 

    Square(const Square& sq); // Конструктор копирования
    Square(Square&& sq) noexcept; // Конструктор перемещения

    Square& operator=(const Square& sq); // Оператор копирования
    Square& operator=(Square&& sq) noexcept; // Оператор перемещения
    
    bool operator==(const Square& other) const; // Сравнение на равенство

    operator double() const override; // Переопределение double для получения площади
    Vertex getCenter() const override; // Получение геометрического центра

    friend std::ostream& operator<<(std::ostream& os, const Square& sq);
    friend std::istream& operator>>(std::istream& is, Square& sq);

private:
    Vertex vertex;
    double width; 
};
