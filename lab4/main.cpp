#include <iostream>
#include "vertex.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
#include "figurearray.h"

int main() {

    FigureArray<Figure<int>*> array;

    array.pushBack(new Square<int>(Vertex<int>(1, 5), 4)); 
    array.pushBack(new Rectangle<int>(Vertex<int>(0, 4), 4, 2));
    std::cout << "Total area: " << array.totalArea() << std::endl;
    array.erase(0);
    std::cout << "Total area: " << array.totalArea() << std::endl;
    array.pushBack(new Triangle<int>({Vertex<int>(0, 0), Vertex<int>(3, 0), Vertex<int>(0, 3)}));
    std::cout << "Total area: " << array.totalArea() << std::endl;
    
    FigureArray<Square<int>> array1;
    
    array1.pushBack(Square<int>(Vertex<int>(0, 0), 5));
    array1.pushBack(Square<int>(Vertex<int>(1, 1), 5));
    double area = 0.0;
    for (size_t i = 0; i < array1.size(); ++i) {
        std::cout << "Square " << i << ": " << array1[i] << std::endl;
        area += double(array1[i]);
    }
    std::cout << "Total area array of squares: " << area << std::endl;

    return 0;
}
