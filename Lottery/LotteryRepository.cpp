#include "LotteryRepository.h"

#include <fstream>

using namespace std;

LotteryRepository::LotteryRepository() {
}

string LotteryRepository::readFileContentToString(string filepath) {
    string result = "";

    ifstream in(filepath.c_str());

    if(in.is_open()) {
        string line;
        while(getline(in, line)) {
            result += line + "\n";
        }
    }

    in.close();

    return result;
}

string LotteryRepository::getLotteryHeaderMessage() {
    return readFileContentToString("templates/lottery-header.txt");
}

string LotteryRepository::getLotteryBeginMessage() {
    return readFileContentToString("templates/lottery-letsbegin.txt");
}

string LotteryRepository::getLotteryResultsHeaderMessage() {
    return readFileContentToString("templates/lottery-results.txt");
}

vector<int> LotteryRepository::getExcludedNumbers() {
    vector<int> result;

    ifstream in("excluded.txt");

    if(in.is_open()) {
        int nextNumber;
        while(in >> nextNumber) {
            result.push_back(nextNumber);
        }
    }

    in.close();

    return result;
}

void LotteryRepository::saveLottery(Lottery lottery) {
    ofstream out("results.txt");

    vector<int> lotteryNumbers = lottery.getNumbers();

    if(out.is_open()) {
        for(unsigned int i = 0; i < lotteryNumbers.size(); ++i) {
            out << lotteryNumbers[i] << endl;
        }
    }

    out.close();

    // Open the file and append this to whatever is in there already
    out.open("excluded.txt", ofstream::app);

    if(out.is_open()) {
        for(unsigned int i = 0; i < lotteryNumbers.size(); ++i) {
            out << lotteryNumbers[i] << endl;
        }
    }

    out.close();
}
