#include "iostream"
#include "ClockConverter.h"
#include <string>

int main(){
    int hour, minute;
    std::string period;
    std::string time12;

    std::cout << "Преобразование 12-часового времени в 24-часовое." << std::endl;
    std::cout << "Введите час(от 1 до 12): ";
    std::cin >> hour;
    while (ClockConverter(hour, 0, "pm").length() > 5){
        std::cout << ClockConverter(hour, 0, "pm") << "Введите час еще раз: ";
        std::cin >> hour;
    }
    std::cout << "Введите минуты(от 0 до 59): ";
    std::cin >> minute;
    while (ClockConverter(1, minute, "pm").length() > 5){
        std::cout << ClockConverter(1, minute, "pm") << "Введите минуты еще раз: ";
        std::cin >> minute;
    }
    std::cout << "Введите период(am или pm): ";
    std::cin >> period;
    while (ClockConverter(1, 0, period).length() > 5){
        std::cout << ClockConverter(1, 0, period) << "Введите период еще раз: ";
        std::cin >> period;
    }

    std::cout << "Время в 24-часовом формате: " << ClockConverter(hour, minute, period) << std::endl;

    return 0;
}
