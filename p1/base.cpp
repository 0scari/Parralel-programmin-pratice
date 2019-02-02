#include <cmath>
#include <cstdlib>
#include <thread>
#include <sstream>

#include "helpers.cpp"

using namespace std;

void task1(){
    thread t1(helpers::printNumber, 1);
    thread t2(helpers::printNumber, 2);

    // This join after thread launch is important, since without it,
    // if your main function exits with tasks still on the stack
    // there will be unpredictable behaviour, possibly crashes.
    t1.join();
    t2.join();
}

void task2(vector<string> lines){
    int pos = 0;
    while (pos < lines.size()){
        thread t1(helpers::nextPos, pos);
        thread t2(helpers::printLine, 2, lines);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main (void)
{
    task1();
    vector<string> textLines = helpers::readFileLines
            ("/Users/oskarspozdnakovs/Mac Storage/370ct/p1/caged_bird.txt");
    task2(textLines);
    return 0;
}
