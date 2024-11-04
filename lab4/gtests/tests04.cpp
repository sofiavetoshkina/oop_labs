#include <gtest/gtest.h>
#include "figurearray.h"
#include "vertex.h"
#include "figure.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"

TEST(TriangleTests, TriangleCenter){
    std::vector<Vertex<double>> tr_vertices = {
        Vertex(0.0, 0.0),
        Vertex(3.0, 0.0),
        Vertex(0.0, 3.0)
    };
    Triangle<double> tr(tr_vertices);
    Vertex<double> center = tr.getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 1.0);
    EXPECT_DOUBLE_EQ(center.getY(), 1.0);
}
TEST(TriangleTests, TriangleArea) {
    Triangle<double> tr({ {0.0, 0.0}, {3.0, 0.0}, {0.0, 3.0} });
    double answer = 4.5;
    EXPECT_DOUBLE_EQ(double(tr), answer);
}

TEST(TriangleTests, TrianglesEqual) {
    Triangle<int> tr1({ {0, 0}, {1, 1}, {2, 0} });
    Triangle<int> tr2({ {0, 0}, {2, 0}, {1, 1} });
    ASSERT_TRUE(tr1 == tr2);
}

TEST(SquareTests, SquareCenter){
    Square<int> sq({1, 5}, 4);
    Vertex<int> center = sq.getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 3);
    EXPECT_DOUBLE_EQ(center.getY(), 3);
}

TEST(SquareTests, SquareArea) {
    Square<int> sq({1, 5}, 4);
    double answer = 16.0;
    EXPECT_DOUBLE_EQ(double(sq), answer);
}

TEST(RectangleTests, RectangleCenter){
    Rectangle<double> r({1.0, 5.0}, 4.0, 3.0); 
    Vertex<double> center = r.getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 3.0);
    EXPECT_DOUBLE_EQ(center.getY(), 3.5);
}

TEST(RectangleTests, RectangleArea) {
    Rectangle<int> r({1, 5}, 4, 3);
    double answer = 12.0;
    EXPECT_DOUBLE_EQ(double(r), answer);
}

TEST(FigureArray, TotalAreaSquare) {
    FigureArray<Figure<int>*> array;
    array.pushBack(new Square<int>(Vertex<int>(0, 0), 1));
    array.pushBack(new Square<int>(Vertex<int>(0, 0), 2));
    array.pushBack(new Square<int>(Vertex<int>(0, 0), 3));
    double answer = 14.0;
    EXPECT_DOUBLE_EQ(array.totalArea(), answer);
}

TEST(FigureArray, TotalAreaWithErase) {
    FigureArray<Figure<int>*> array;
    array.pushBack(new Square<int>(Vertex<int>(1, 5), 4)); 
    array.pushBack(new Rectangle<int>(Vertex<int>(0, 4), 4, 2));
    array.erase(0); // Удаляем по индексу 0
    array.pushBack(new Triangle<int>({Vertex<int>(0, 0), Vertex<int>(3, 0), Vertex<int>(0, 3)}));
    double answer = 12.5;
    EXPECT_DOUBLE_EQ(array.totalArea(), answer);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}