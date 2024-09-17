#include <gtest/gtest.h>
#include "ClockConverter.h"

TEST(tests01, evening){
    ASSERT_TRUE(ClockConverter(7, 30, "pm")=="19:30");
}

TEST(tests01, morning){
    ASSERT_TRUE(ClockConverter(7, 30, "am")=="07:30");
}

TEST(tests01, day){
    ASSERT_TRUE(ClockConverter(1, 59, "pm")=="13:59");
}

TEST(tests01, midnight){
    ASSERT_TRUE(ClockConverter(12, 0, "am")=="00:00");
}

TEST(tests01, noon){
    ASSERT_TRUE(ClockConverter(12, 0, "pm")=="12:00");
}

TEST(tests01, invalid_hour){
    ASSERT_TRUE(ClockConverter(0, 0, "am")=="Ошибка. Вы неправильно ввели время(час от 1 до 12).");
}

TEST(tests01, invalid_minute){
    ASSERT_TRUE(ClockConverter(1, 60, "am")=="Ошибка. Вы неправильно ввели время(минуты от 0 до 59).");
}

TEST(tests01, invalid_period){
    ASSERT_TRUE(ClockConverter(1, 0, "aa")=="Ошибка. Вы неправильно ввели период(pm или am).");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}