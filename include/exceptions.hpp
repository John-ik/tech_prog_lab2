#pragma once

#include <stdexcept>

// Ошибка ввода или обращения к элементу. Текст поясняет возникшую ситуацию.
class TrainError : public std::runtime_error {
  public:
    using std::runtime_error::runtime_error;
};
