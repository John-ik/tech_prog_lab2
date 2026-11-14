#pragma once

#include "exceptions.hpp"

#include <exception>
#include <iostream>
#include <string>

// Строка целиком. Конец ввода — исключение.
inline std::string readLine(std::istream &is) {
    std::string line;
    if (!std::getline(is, line))
        throw TrainError("достигнут конец ввода");
    return line;
}

// Целое число. Лишние символы после числа — ошибка.
inline int parseInt(const std::string &text, const std::string &what) {
    std::size_t pos = 0;
    int value = 0;
    try {
        value = std::stoi(text, &pos);
    } catch (const std::exception &) {
        pos = 0;
    }
    if (pos == 0 || pos != text.size())
        throw TrainError(what + ": ожидалось целое число, получено \"" + text + "\"");
    return value;
}

// Время вида ЧЧ:ММ. Диапазон проверяется в checkTime.
inline void parseTime(const std::string &text, int &hour, int &minute) {
    const std::size_t colon = text.find(':');
    if (colon == std::string::npos)
        throw TrainError("время должно быть в формате ЧЧ:ММ, получено \"" + text + "\"");
    hour = parseInt(text.substr(0, colon), "часы");
    minute = parseInt(text.substr(colon + 1), "минуты");
}

// Время суток: 00:00..23:59.
inline void checkTime(int hour, int minute) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
        throw TrainError("время вне диапазона 00:00..23:59");
}
