#pragma once

#include "vertex.h"

template <typename T>
class Figure 
{
public:
    virtual Vertex<T> getCenter() const = 0; // Получение геометрического центра
    virtual operator double() const = 0; // Получение площади через double()
    virtual ~Figure() = default; // Деструктор
};