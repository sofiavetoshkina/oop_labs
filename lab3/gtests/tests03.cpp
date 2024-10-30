#include <gtest/gtest.h>
#include "figurearray.h"
#include "vertex.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"

TEST(TriangleTests, TriangleCenter){
    std::vector<Vertex> tr_vertices = {
        Vertex(0.0, 0.0),
        Vertex(3.0, 0.0),
        Vertex(0.0, 3.0)
    };
    Triangle tr(tr_vertices);
    Vertex center = tr.getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 1.0);
    EXPECT_DOUBLE_EQ(center.getY(), 1.0);
}

TEST(TriangleTests, TriangleArea) {
    Triangle tr({ {0.0, 0.0}, {3.0, 0.0}, {0.0, 3.0} });
    double answer = 4.5;
    EXPECT_DOUBLE_EQ(double(tr), answer);
}

TEST(TriangleTests, TrianglesEqual) {
    Triangle tr1({ {0.0, 0.0}, {1.0, 1.0}, {2.0, 0.0} });
    Triangle tr2({ {0.0, 0.0}, {2.0f, 0.0}, {1.0f, 1.0} });
    ASSERT_TRUE(tr1 == tr2);
}

TEST(SquareTests, SquareCenter){
    Square sq({1.0, 5.0}, 4.0);
    Vertex center = sq.getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 3.0);
    EXPECT_DOUBLE_EQ(center.getY(), 3.0);
}

TEST(SquareTests, SquareArea) {
    Square sq({1.0, 5.0}, 4.0);
    double answer = 16.0;
    EXPECT_DOUBLE_EQ(double(sq), answer);
}

TEST(RectangleTests, RectangleCenter){
    Rectangle r({1.0, 5.0}, 4.0, 3.0); 
    Vertex center = r.getCenter();
    EXPECT_DOUBLE_EQ(center.getX(), 3.0);
    EXPECT_DOUBLE_EQ(center.getY(), 3.5);
}

TEST(RectangleTests, RectangleArea) {
    Rectangle r({1.0, 5.0}, 4.0, 3.0);
    double answer = 12.0;
    EXPECT_DOUBLE_EQ(double(r), answer);
}

TEST(FigureArray, TotalArea) {
    FigureArray array;
    Square sq({1.0, 5.0}, 4.0);
    Triangle tr({ {-1.0, 0.0}, {1.0, 4.0}, {3.0, 0.0} });
    Rectangle r({1.0, 5.0}, 4.0, 3.0); 
    array.pushBack(&tr);
    array.pushBack(&sq);
    array.pushBack(&r);
    double answer = 36.0;
    EXPECT_DOUBLE_EQ(array.totalArea(), answer);
}

TEST(FigureArray, TotalAreaWithErase) {
    FigureArray array;
    Square sq({1.0, 5.0}, 4.0);
    Triangle tr({ {-1.0, 0.0}, {1.0, 4.0}, {3.0, 0.0} });
    Rectangle r({1.0, 5.0}, 4.0, 3.0); 
    array.pushBack(&tr);
    array.pushBack(&sq);
    array.pushBack(&r);
    array.erase(1); // Удаляем фигуру по индексу 1
    double answer = 20.0;
    EXPECT_DOUBLE_EQ(array.totalArea(), answer);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}