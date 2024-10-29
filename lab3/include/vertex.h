#pragma once

#include <iostream>

class Vertex 
{
public:
    Vertex(); // Конструктор по умолчанию
    Vertex(double x_in, double y_in); // Конструктор с координатами (x, y) вершины

    Vertex(const Vertex& other); // Конструктор копирования
    Vertex(Vertex&& other) noexcept; // Конструктор перемещения

    double getX() const; // Метод для получения значения x
    double getY() const; // Метод для получения значения y

    Vertex& operator=(const Vertex& other); // Оператор копирования
    Vertex& operator=(Vertex &&other) noexcept; // Оператор перемещения

	Vertex operator+(const Vertex& other) const; // Оператор сложения координат двух вершин
	Vertex operator-(const Vertex& other) const; // Оператор вычитания координат двух вершин

	Vertex& operator+=(const Vertex& other);
	Vertex& operator-=(const Vertex& other);

	bool operator==(const Vertex& other) const; // Оператор проверки на равенство
    
	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);
	friend std::istream& operator>>(std::istream& is, Vertex& vertex);

private:
    double _x;
    double _y;
};