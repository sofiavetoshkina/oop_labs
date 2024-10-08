#pragma once

#include <iostream>
#include <initializer_list>
#include <string>

class Three
{
public:
    Three(); // Конструктор по умолчанию
    Three(unsigned int number); // Конструктор принимает беззнаковое десятичное, преобразуя его в троичное
    Three(const std::initializer_list<unsigned char>& t); // Конструктор с списком инициализации
    Three(const std::string& t); // Конструктор с string

    Three(const Three& other); // Конструктор копирования
    Three(Three&& other) noexcept; // Конструктор перемещения

    Three add(const Three& other) const; // Сложение двух троичных чисел
    Three subtract(const Three& other) const; // Вычитание

    bool equals(const Three& other) const; // Являются ли 2 числа равными
    bool less_than(const Three& other) const; // Является ли число меньше другого
    bool greater_than(const Three& other) const; // Является ли число больше другого

    bool operator >(const Three& other) const; // Оператор для проверки на "больше"
    bool operator >=(const Three& other) const; // Оператор для проверки на "больше или равно"
    bool operator <(const Three& other) const; // Оператор для проверки на "меньше"
    bool operator <=(const Three& other) const; // Оператор для проверки на "меньше или равно"
    
    Three operator +(const Three& other) const; // Оператор сложения
    Three operator -(const Three& other) const; // Оператор вычитания
    
    Three& operator =(const Three& other); // Оператор копирования
    Three& operator =(Three&& other) noexcept; // Оператор перемещения
    
    std::ostream& print(std::ostream& os); // Метод для вывода числа

    ~Three() noexcept; // Деструктор

private:
    size_t _size;
    unsigned char* _array;
    static bool isTernary(const unsigned char& digit);
};
