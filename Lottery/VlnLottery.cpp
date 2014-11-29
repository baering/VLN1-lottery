#include "VlnLottery.h"

#include <iostream>

// Need this to use command-line commands
#include <cstdlib>

// Need this to use clock()
#include <ctime>

// Need this for the Sleep() function (only compiles on Windows)
// Have a look at the usleep() function from <unistd.h> for unix based systems
#include <windows.h>

using namespace std;


VlnLottery::VlnLottery() {
}

void VlnLottery::start() {
    cout << lotteryService.getLotteryHeaderMessage();
    system("pause");
    system("cls");

    cout << lotteryService.getLotteryBeginMessage();

    startSong();

    system("pause");
    system("cls");

    startLottery();

    system("pause");
}

void VlnLottery::startSong() {
    system("start chrome https://www.youtube.com/watch?v=DhlPAj38rHc");
}

void VlnLottery::startLottery() {
    string selectedGroupsHeader = lotteryService.getLotteryResultsHeaderMessage();

    Lottery lottery;

    printSelectedNumbers(selectedGroupsHeader, lottery);

    // I used this to count milliseconds each iteration takes in order for new group number
    // to spawn in perfect sync with the song being played in the background
    int timeLastIterationTook = 0;
    int timeStartedToCalculate = 0;

    while(lottery.currentSize() < 20) {
        // Subtract the time it took to calculate all the stuff in last iteration from
        // the time the program will sleep for in this iteration to keep sync with the song
        int sleepTime = -timeLastIterationTook;

        // The beat of the song is 94 BPM - I wanted a new number to be generated every 2 beats
        // (60 / 94) * 1000 = 1.276,6
        // Since we only have integer precision for the sleep function we have to imitate the
        // extra precision by changing between 1277 and 1276 ms in every iteration
        if(lottery.currentSize() % 2 == 0) {
            sleepTime += 1276;
        }
        else {
            sleepTime += 1277;
        }

        Sleep(sleepTime);

        // Since we're working with precision in milliseconds we need to take the time it takes
        // to find a random number into account for perfect sync with the song

        timeStartedToCalculate = clock();

        int nextNumber = lotteryService.getNextNumber(lottery);
        lottery.addNumber(nextNumber);

        printSelectedNumbers(selectedGroupsHeader, lottery);

        timeLastIterationTook = clock() - timeStartedToCalculate;
    }

    lotteryService.saveLottery(lottery);
}

string numberToString(int number, unsigned int width) {
    string result = "";

    do {
        // Cut the rightmost digit of the number in each iteration
        // add it to the result and then shift the number to the right

        result.insert(result.begin(), static_cast<char>(48 + (number % 10)));

        number = number / 10;
    } while(number > 0);

    if(result.length() < width) {
        int difference = width - result.length();

        string zeroPrefix(difference, '0');
        result.insert(0, zeroPrefix);
    }

    return result;
}

void VlnLottery::printSelectedNumbers(string header, Lottery& lottery) {
    vector<int> numbers = lottery.getNumbers();

    system("cls");

    cout << header;

    int groupsInCurrentLine = 0;

    // Ugly formatting code below this point :)

    cout << "\t\t\t--------------------------\n";
    cout << "\t\t\t|";
    for(unsigned int i = 0; i < 20; ++i) {

        if(i < numbers.size()) {
            // Print the current number inside the correct column
            int currentNumber = numbers[i];
            cout << " " << numberToString(currentNumber, 2) << " |";
        }
        else {
            // Print an empty column if we don't have enough numbers yet
            cout << "    |";
        }

        ++groupsInCurrentLine;

        // Only print 5 numbers in each row
        if(groupsInCurrentLine > 4) {
            cout << "\n\t\t\t--------------------------\n";

            if(i + 1 < 20) {
                cout << "\t\t\t|";
            }

            groupsInCurrentLine = 0;
        }
    }
    cout << "\n\n\n\n\n" << endl;
}
