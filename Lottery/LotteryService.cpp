#include "LotteryService.h"

// For the random numbers
#include <cstdlib>

// To get access to time(NULL) which returns seconds since 1. january 1970
#include <ctime>

using namespace std;

LotteryService::LotteryService() {
    // Initialize the random generator with time since 1. january 1970
    // You can read more about it here: http://www.cplusplus.com/reference/cstdlib/srand/
    srand(time(NULL));

    excludedNumbers = lotteryRepository.getExcludedNumbers();
}

string LotteryService::getLotteryHeaderMessage() {
    return lotteryRepository.getLotteryHeaderMessage();
}

string LotteryService::getLotteryBeginMessage() {
    return lotteryRepository.getLotteryBeginMessage();
}

string LotteryService::getLotteryResultsHeaderMessage() {
    return lotteryRepository.getLotteryResultsHeaderMessage();
}

bool LotteryService::numberIsInVector(vector<int> numbers, int number) {
    for(unsigned int i = 0; i < numbers.size(); ++i) {
        if(numbers[i] == number) {
            return true;
        }
    }
    return false;
}

int LotteryService::getNextNumber(Lottery& lottery) {
    int nextNumber;

    do {
        // Get a random number between 1 and 61 (inclusive)
        nextNumber = rand() % 61 + 1;
    } while(numberIsInVector(lottery.getNumbers(), nextNumber) || numberIsInVector(excludedNumbers, nextNumber));

    return nextNumber;
}

vector<int> LotteryService::getExludedNumbers() {
    return lotteryRepository.getExcludedNumbers();
}

void LotteryService::saveLottery(Lottery lottery) {
    lotteryRepository.saveLottery(lottery);
}
