#include "ClockConverter.h"
#include <string>

std::string ClockConverter(int hour, int minute, const std::string period){

    std::string result;

    if (hour < 1 || hour > 12){
        return "Ошибка. Вы неправильно ввели время(час от 1 до 12).";
    }
    if (minute < 0 || minute > 59){
        return "Ошибка. Вы неправильно ввели время(минуты от 0 до 59).";
    }
    if (period != "pm" && period != "am"){
        return "Ошибка. Вы неправильно ввели период(pm или am).";
    }

    //12:00 am полночь, 12:00 pm полдень
    if (period == "pm" && hour != 12){
        hour += 12;
    }
    else if (period == "am" && hour == 12){
        hour = 0;
    }


    result = std::to_string(hour);

    if (hour < 10){
        result = "0" + result;
    }
    result += ":";
    if (minute < 10){
        result += "0";
    }
    result += std::to_string(minute);

    return result;
}
