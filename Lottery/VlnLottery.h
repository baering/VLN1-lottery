#ifndef VLNLOTTERY_H
#define VLNLOTTERY_H

#include "LotteryService.h"

class VlnLottery
{
    public:
        VlnLottery();
        void start();
    private:
        void startSong();
        void startLottery();
        void printSelectedNumbers(std::string header, Lottery& lottery);

        LotteryService lotteryService;
};

#endif // VLNLOTTERY_H
