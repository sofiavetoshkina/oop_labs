#include <gtest/gtest.h>
#include "Three.h"

// Тест конструктора(преобразует беззнаковое десятичное число в троичное)
TEST(tests02, decimal_number){
    Three t(12);
    std::stringstream os1, os2;
    t.print(os1);
    os2 << "110";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест конструктора с инициализированным списком
TEST(tests02, initializer_list){
    Three t{'1', '0', '0', '2'};
    std::stringstream os1, os2;
    t.print(os1);
    os2 << "1002";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест конструктора с строкой
TEST(tests02, string){
    Three t("1002");
    std::stringstream os1, os2;
    t.print(os1);
    os2 << "1002";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест конструктора копирования
TEST(tests02, copy){
    Three t("12");
    Three t1(t);
    std::stringstream os1, os2;
    t.print(os1);
    t1.print(os2);
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест конструктора перемещения
TEST(tests02, move){
    Three t("12");
    Three t1(std::move(t));
    std::stringstream os1, os2;
    t1.print(os1);
    os2 << "12";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест метода сложения двух троичных чисел 
TEST(tests02, add_1){
    Three t1{'1', '0', '0', '2'};
    Three t2("111");
    Three result = t1.add(t2);
    std::stringstream os1, os2;
    result.print(os1);
    os2 << "1120";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест метода сложения двух троичных чисел 
TEST(tests02, add_2){
    Three t1{'2', '2', '2'};
    Three t2("222");
    Three result = t1.add(t2);
    std::stringstream os1, os2;
    result.print(os1);
    os2 << "1221";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест вычитания двух троичных чисел
TEST(tests02, subtract_1){
    Three t1{'2', '2', '2'};
    Three t2("222");
    Three result = t1.subtract(t2);
    std::stringstream os1, os2;
    result.print(os1);
    os2 << "0";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест вычитания двух троичных чисел
TEST(tests02, subtract_2){
    Three t1{'1', '1', '1'};
    Three t2("22");
    Three result = t1.subtract(t2);
    std::stringstream os1, os2;
    result.print(os1);
    os2 << "12";
    ASSERT_EQ(os1.str(), os2.str());
}

// Тест на равенство
TEST(tests02, eq_1){
    Three t1{'2', '2', '2'};
    Three t2("222");
    ASSERT_TRUE(t1.equals(t2));
}

TEST(tests02, eq_2){
    Three t1{'2', '2', '2'};
    Three t2("221");
    ASSERT_FALSE(t1.equals(t2));
}

// Тест является ли число меньше другого 
TEST(tests02, lt_1){
    Three t1{'2', '2', '2'};
    Three t2("221");
    ASSERT_FALSE(t1.less_than(t2));
}

TEST(tests02, lt_2){
    Three t1{'2', '2', '1'};
    Three t2("222");
    ASSERT_TRUE(t1.less_than(t2));
}

// Тест является ли число больше другого 
TEST(tests02, gt_1){
    Three t1{'2', '2', '2'};
    Three t2("21");
    ASSERT_TRUE(t1.greater_than(t2));
}

TEST(tests02, gt_2){
    Three t1{'2', '2'};
    Three t2("222");
    ASSERT_FALSE(t1.greater_than(t2));
}

//Тесты на ошибки
TEST(tests02, exception_1){
    ASSERT_THROW(Three t("140"), std::invalid_argument);
}

TEST(tests02, exception_2){
    Three t1{'2', '2'};
    Three t2("222");
    ASSERT_THROW(t1.subtract(t2), std::range_error);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}