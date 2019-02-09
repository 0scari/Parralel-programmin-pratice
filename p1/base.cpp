#include <cmath>
#include <cstdlib>
#include <thread>
#include <sstream>



#include "helpers.h"

using namespace std;

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
    vector<string> textLines = helpers::readFileLines
            ("./caged_bird.txt");
    task2(textLines);
    return 0;
}
