#include "exceptions.hpp"
#include "input.hpp"
#include "train.hpp"
#include "train_list.hpp"

#include <cstddef>
#include <iostream>
#include <string>

namespace {

void printHelp() {
    std::cout << "\nКоманды:\n"
                 "  p - показать все поезда\n"
                 "  a - добавить поезд в конец\n"
                 "  i - добавить поезд на позицию\n"
                 "  e - редактировать поезд\n"
                 "  d - удалить поезд\n"
                 "  s - отсортировать по пункту назначения\n"
                 "  t - поезда, отправляющиеся после времени\n"
                 "  h - помощь\n"
                 "  q - выход\n";
}

// Позиция от 1 до max. Возвращает индекс с нуля.
std::size_t readPosition(std::size_t max) {
    if (max == 0)
        throw TrainError("список пуст");
    std::cout << "Позиция (1.." << max << "): ";
    const int position = parseInt(readLine(std::cin), "позиция");
    if (position < 1 || static_cast<std::size_t>(position) > max)
        throw TrainError(
            "позиция " + std::to_string(position) + " вне диапазона 1.." + std::to_string(max));
    return static_cast<std::size_t>(position) - 1;
}

void printAll(const TrainList &list) {
    if (list.size() == 0) {
        std::cout << "Список пуст.\n";
        return;
    }
    for (std::size_t i = 0; i < list.size(); ++i)
        std::cout << i + 1 << ". " << list.at(i) << '\n';
}

void addToEnd(TrainList &list) {
    Train Train;
    std::cin >> Train;
    list.insert(list.size(), Train);
}

void addAtPosition(TrainList &list) {
    const std::size_t index = readPosition(list.size() + 1);
    Train Train;
    std::cin >> Train;
    list.insert(index, Train);
}

void editTrain(TrainList &list) {
    const std::size_t index = readPosition(list.size());
    Train Train;
    std::cin >> Train;
    list.replace(index, Train);
}

void removeTrain(TrainList &list) { list.removeAt(readPosition(list.size())); }

void printAfterTime(const TrainList &list) {
    std::cout << "Время (ЧЧ:ММ): ";
    const std::string text = readLine(std::cin);
    int hour = 0;
    int minute = 0;
    parseTime(text, hour, minute);
    checkTime(hour, minute);
    const int after = hour * 60 + minute;

    bool found = false;
    for (std::size_t i = 0; i < list.size(); ++i) {
        if (list.at(i).departureMinutes() > after) {
            std::cout << i + 1 << ". " << list.at(i) << '\n';
            found = true;
        }
    }
    if (!found)
        std::cout << "Поездов, отправляющихся после " << text << ", нет.\n";
}

} // namespace

int main() {
    TrainList list;
    std::cout << "Введите команду (h - помощь)\n";
    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line))
            break;

        try {
            const char command = line.size() == 1 ? line[0] : '\0';
            switch (command) {
            case 'q':
                return 0;
            case 'p':
                printAll(list);
                break;
            case 'a':
                addToEnd(list);
                break;
            case 'i':
                addAtPosition(list);
                break;
            case 'e':
                editTrain(list);
                break;
            case 'd':
                removeTrain(list);
                break;
            case 's':
                list.sortByDestination();
                printAll(list);
                break;
            case 't':
                printAfterTime(list);
                break;
            case 'h':
                printHelp();
                break;
            default:
                std::cout << "Ошибка: неизвестная команда \"" << line << "\"\n";
                printHelp();
            }
        } catch (const TrainError &e) {
            std::cout << "Ошибка: " << e.what() << '\n';
        }
    }
    return 0;
}
