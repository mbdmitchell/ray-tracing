#include "Countdown.h"

Countdown::Countdown(size_t number) : number{number} {}

void Countdown::log() const {
    std::clog << "\rScanlines remaining: " << number << ' ' << std::flush;
}

Countdown &Countdown::operator--() {
    --number;
    return *this;
}

Countdown::~Countdown() {
    std::clog << "\rDone.                      \n";
}
