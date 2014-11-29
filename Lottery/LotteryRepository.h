#ifndef LOTTERYREPOSITORY_H
#define LOTTERYREPOSITORY_H

#include "Lottery.h"
#include <string>

class LotteryRepository
{
    public:
        LotteryRepository();

        std::string getLotteryHeaderMessage();
        std::string getLotteryBeginMessage();
        std::string getLotteryResultsHeaderMessage();

        std::vector<int> getExcludedNumbers();

        void saveLottery(Lottery lottery);
    private:
        std::string readFileContentToString(std::string filepath);
};

#endif // LOTTERYREPOSITORY_H
