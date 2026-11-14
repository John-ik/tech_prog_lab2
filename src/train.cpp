#include "train.hpp"

#include "exceptions.hpp"
#include "input.hpp"
#include "log.hpp"

#include <iomanip>

Train::Train() : hour(0), minute(0) { logLifecycle(label(), "конструктор по умолчанию", this); }

Train::Train(const std::string &destination, const std::string &number, int hour, int minute)
    : hour(0), minute(0) {
    setDestination(destination);
    setNumber(number);
    setTime(hour, minute);
    logLifecycle(label(), "конструктор с параметрами", this);
}

Train::Train(const Train &other)
    : destination(other.destination), number(other.number), hour(other.hour), minute(other.minute) {
    logLifecycle(label(), "конструктор копирования", this);
}

Train &Train::operator=(const Train &other) {
    destination = other.destination;
    number = other.number;
    hour = other.hour;
    minute = other.minute;
    return *this;
}

Train::~Train() { logLifecycle(label(), "деструктор", this); }

std::string Train::label() const { return "Train \"" + destination + "\""; }

const std::string &Train::getDestination() const { return destination; }

const std::string &Train::getNumber() const { return number; }

int Train::getHour() const { return hour; }

int Train::getMinute() const { return minute; }

void Train::setDestination(const std::string &value) {
    if (value.empty())
        throw TrainError("пункт назначения не может быть пустым");
    destination = value;
}

void Train::setNumber(const std::string &value) {
    if (value.empty())
        throw TrainError("номер поезда не может быть пустым");
    number = value;
}

void Train::setTime(int h, int m) {
    checkTime(h, m);
    hour = h;
    minute = m;
}

int Train::departureMinutes() const { return hour * 60 + minute; }

std::istream &operator>>(std::istream &is, Train &train) {
    std::cout << "Пункт назначения: ";
    const std::string destination = readLine(is);
    std::cout << "Номер поезда: ";
    const std::string number = readLine(is);
    std::cout << "Время отправления (ЧЧ:ММ): ";
    int hour = 0;
    int minute = 0;
    parseTime(readLine(is), hour, minute);

    train = Train(destination, number, hour, minute);
    return is;
}

std::ostream &operator<<(std::ostream &os, const Train &train) {
    os << train.getDestination() << ", поезд №" << train.getNumber() << ", отправление "
       << std::setfill('0') << std::setw(2) << train.getHour() << ':' << std::setw(2)
       << train.getMinute() << std::setfill(' ');
    return os;
}
