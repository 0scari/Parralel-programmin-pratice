#include <cmath>
#include <cstdlib>
#include <thread>
#include <sstream>



#include "helpers.h"

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
    int pos = -1;
    int size = lines.size();
    while (pos < size){
        thread t1(helpers::nextPos, &pos);
        t1.join();
        this_thread::sleep_for(chrono::milliseconds(1000));
        thread t2(helpers::printLine, pos, lines);
        t2.join();
    }
}

int main (void)
{
    task1();
    //TODO change to relative path
    vector<string> textLines = helpers::readFileLines
            ("./caged_bird.txt");
    task2(textLines);
    return 0;
}
