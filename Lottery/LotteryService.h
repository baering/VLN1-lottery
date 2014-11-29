#ifndef LOTTERYSERVICE_H
#define LOTTERYSERVICE_H

#include "lotteryrepository.h"

class LotteryService
{
    public:
        LotteryService();

        std::string getLotteryHeaderMessage();
        std::string getLotteryBeginMessage();
        std::string getLotteryResultsHeaderMessage();

        int getNextNumber(Lottery& lottery);
        std::vector<int> getExludedNumbers();

        void saveLottery(Lottery lottery);
    private:
        bool numberIsInVector(std::vector<int> numbers, int number);

        LotteryRepository lotteryRepository;
        std::vector<int> excludedNumbers;
};

#endif // LOTTERYSERVICE_H
