#pragma once

#include <iostream>

class Countdown {
    size_t number;
public:
    explicit Countdown(size_t number);
    ~Countdown();

    void log() const;
    Countdown& operator --();
};