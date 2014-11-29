#include "Lottery.h"

Lottery::Lottery() {
}

void Lottery::addNumber(int number) {
    numbers.push_back(number);
}

std::vector<int> Lottery::getNumbers() {
    return numbers;
}

unsigned int Lottery::currentSize() {
    return numbers.size();
}
