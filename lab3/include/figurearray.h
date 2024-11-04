#pragma once

#include <initializer_list>
#include "figure.h"  

class FigureArray 
{
public:
    FigureArray();
    FigureArray(size_t n);
    ~FigureArray();

    FigureArray(const FigureArray& other); // Конструктор копирования
    FigureArray(FigureArray&& other) noexcept; // Конструктор перемещения

    Figure* & operator[] (size_t ind);  // Оператор доступа к элементу массива по индексу (для изменения)
    Figure* & operator[] (size_t ind) const; // Оператор доступа к элементу массива по индексу (для чтения)

    size_t size() const;
    void resize(size_t newSize);
    void pushBack(Figure* figure); // Метод для добавления элемента в конец массива
    void erase(size_t ind); // Метод для удаления элемента по индексу
    double totalArea(); // Метод для возвращения общей площади фигур
    
private:
    size_t curSize, capacity; 
    Figure** data; 

    void setCapacity(size_t value);  // Метод для изменения вместимости массива
    static Figure** reallocate(Figure** oldData, size_t oldSize, size_t newSize);  // Метод для перераспределения памяти под массив указателей

};