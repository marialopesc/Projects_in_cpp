#include "Register.hpp"

Register::Register() : value(0) {}

int Register::getValue() const {
    return value;
}

void Register::setValue(int newValue) {
    value = newValue;
}

void Register::reset() {
    value = 0;
}
