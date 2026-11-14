#include "train_list.hpp"

#include "exceptions.hpp"
#include "log.hpp"

#include <string>

TrainList::TrainList() : items(nullptr), count(0), capacity(0) {
    logLifecycle("TrainList", "конструктор по умолчанию", this);
}

TrainList::TrainList(std::size_t initialCapacity)
    : items(new Train *[initialCapacity]), count(0), capacity(initialCapacity) {
    logLifecycle("TrainList", "конструктор с параметрами", this);
}

TrainList::TrainList(const TrainList &other)
    : items(new Train *[other.count]), count(0), capacity(other.count) {
    for (std::size_t i = 0; i < other.count; ++i)
        items[count++] = new Train(*other.items[i]);
    logLifecycle("TrainList", "конструктор копирования", this);
}

TrainList &TrainList::operator=(const TrainList &other) {
    if (this != &other) {
        clear();
        for (std::size_t i = 0; i < other.count; ++i)
            insert(count, *other.items[i]);
    }
    return *this;
}

TrainList::~TrainList() {
    logLifecycle("TrainList", "деструктор", this);
    clear();
}

std::size_t TrainList::size() const { return count; }

const Train &TrainList::at(std::size_t index) const {
    checkIndex(index);
    return *items[index];
}

void TrainList::insert(std::size_t index, const Train &train) {
    if (index > count)
        throw TrainError("позиция " + std::to_string(index) + " вне диапазона: записей " +
                         std::to_string(count));
    if (count == capacity)
        grow();
    Train *item = new Train(train);
    for (std::size_t i = count; i > index; --i)
        items[i] = items[i - 1];
    items[index] = item;
    ++count;
}

void TrainList::removeAt(std::size_t index) {
    checkIndex(index);
    delete items[index];
    for (std::size_t i = index + 1; i < count; ++i)
        items[i - 1] = items[i];
    --count;
}

void TrainList::replace(std::size_t index, const Train &train) {
    checkIndex(index);
    *items[index] = train;
}

void TrainList::sortByDestination() {
    for (std::size_t i = 1; i < count; ++i) {
        Train *current = items[i];
        std::size_t j = i;
        while (j > 0 && items[j - 1]->getDestination() > current->getDestination()) {
            items[j] = items[j - 1];
            --j;
        }
        items[j] = current;
    }
}

void TrainList::grow() {
    const std::size_t newCapacity = capacity == 0 ? 1 : capacity * 2;
    Train **newItems = new Train *[newCapacity];
    for (std::size_t i = 0; i < count; ++i)
        newItems[i] = items[i];
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

void TrainList::clear() {
    for (std::size_t i = 0; i < count; ++i)
        delete items[i];
    delete[] items;
    items = nullptr;
    count = 0;
    capacity = 0;
}

void TrainList::checkIndex(std::size_t index) const {
    if (index >= count)
        throw TrainError(
            "индекс " + std::to_string(index) + " вне диапазона: записей " + std::to_string(count));
}
