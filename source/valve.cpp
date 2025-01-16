#include "valve.h"

Valve::Valve(bool _status) : status(_status) {}

void Valve::open_valve() {
    status = true;
}

void Valve::close_valve() {
    status = false;
}

bool Valve::statused() const {
    return status;
}