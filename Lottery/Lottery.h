#ifndef LOTTERY_H
#define LOTTERY_H

#include <vector>

class Lottery
{
    public:
        Lottery();
        void addNumber(int number);
        std::vector<int> getNumbers();

        unsigned int currentSize();
    private:
        std::vector<int> numbers;
};

#endif // LOTTERY_H
