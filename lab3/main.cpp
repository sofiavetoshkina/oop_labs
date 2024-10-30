#include <iostream>
#include <vector>
#include "vertex.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
#include "figurearray.h"

int main(){
    Vertex a(1, 2);
    Vertex b(3, 5);
    std::cout << a << "," << b << std::endl;
    std::cout << (a += b) << "," << (a -= b) << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << a.getX() << ", " << a.getY() << std::endl;

    std::vector<Vertex> tr_vertices = {
        Vertex(-1, 0),
        Vertex(1, 4),
        Vertex(3, 0)
    };
    Triangle tr;
    try {
        tr = Triangle(tr_vertices);
        std::cout << "Triangle: " <<  tr << "; center = " << tr.getCenter() << " ; area = " << double(tr) << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    Triangle tr1;
    try {
        std::cout << "Введите координаты треугольника: ";
        std::cin >> tr1;
        std::cout << "Triangle: " <<  tr1 << "; center = " << tr1.getCenter() << " ; area = " << double(tr1) << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << (tr==tr1) << std::endl;
    tr=tr1;
    std::cout << tr << "; " << tr1 << std::endl;

    Square sq({1, 5}, 4); 
    std::cout << "Square: " << sq << " ; center = " << sq.getCenter() << " ; area = " << double(sq) << std::endl;

    Rectangle r({1, 5}, 4, 3); 
    std::cout << "Rectangle: " << r << " ; center = " << r.getCenter() << " ; area = " << double(r) << std::endl;
    
    FigureArray array;
    array.pushBack(&tr);
    array.pushBack(&sq);
    array.pushBack(&r);
    std::cout << "Текущий размер массива: " << array.size() << std::endl;
    array.erase(1);
    std::cout << "Размер массива после удаления: " << array.size() << std::endl;
    std::cout << "Общая площадь всех фигур в массиве: " << array.totalArea() << std::endl;
    
    return 0;
}