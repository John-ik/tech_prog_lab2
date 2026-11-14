#pragma once

#include <iostream>
#include <string>

// Сообщение о вызове конструктора или деструктора: какой объект и какой вызов.
inline void logLifecycle(const std::string &object, const char *event, const void *self) {
    std::cout << "[" << object << "] " << event << " (адрес " << self << ")\n";
}
