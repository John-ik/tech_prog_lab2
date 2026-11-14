#pragma once

#include "train.hpp"

#include <cstddef>

// Динамический массив указателей на поезда. Список владеет объектами и удаляет их сам.
class TrainList {
  private:
    Train **items;
    std::size_t count;
    std::size_t capacity;

    void grow();
    void clear();
    void checkIndex(std::size_t index) const;

  public:
    TrainList();
    explicit TrainList(std::size_t initialCapacity);
    TrainList(const TrainList &other);
    TrainList &operator=(const TrainList &other);
    ~TrainList();

    std::size_t size() const;
    const Train &at(std::size_t index) const;

    // Вставка копии train на позицию index (0..size).
    // @throw TrainError index вне диапазона
    void insert(std::size_t index, const Train &train);
    // @throw TrainError index вне диапазона
    void removeAt(std::size_t index);
    // @throw TrainError index вне диапазона
    void replace(std::size_t index, const Train &train);
    // Сортировка по пункту назначения по возрастанию (вставками, устойчивая).
    void sortByDestination();
};
