#pragma once

#include <iostream>
#include <string>

// Поезд: пункт назначения, номер и время отправления (ЧЧ:ММ).
class Train {
  private:
    std::string destination;
    std::string number;
    int hour;
    int minute;

    std::string label() const;

  public:
    Train();
    Train(const std::string &destination, const std::string &number, int hour, int minute);
    Train(const Train &other);
    Train &operator=(const Train &other);
    ~Train();

    const std::string &getDestination() const;
    const std::string &getNumber() const;
    int getHour() const;
    int getMinute() const;

    // @throw TrainError пустой пункт назначения
    void setDestination(const std::string &value);
    // @throw TrainError пустой номер
    void setNumber(const std::string &value);
    // @throw TrainError время вне диапазона 00:00..23:59
    void setTime(int hour, int minute);

    // Время отправления в минутах от начала суток.
    int departureMinutes() const;
};

// Ввод с клавиатуры: пункт назначения, номер, время (ЧЧ:ММ). Каждое поле — отдельная строка.
// Объект меняется только при успешном вводе всех полей.
std::istream &operator>>(std::istream &is, Train &train);

// Вывод: "пункт назначения, поезд №номер, отправление ЧЧ:ММ".
std::ostream &operator<<(std::ostream &os, const Train &train);
