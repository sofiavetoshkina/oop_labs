#pragma once

#include "vertex.h"

class Figure 
{
public:
    virtual Vertex getCenter() const = 0; // Получение геометрического центра
    virtual operator double() const = 0; // Получение площади через double()
    virtual ~Figure() = default; // Деструктор
};
