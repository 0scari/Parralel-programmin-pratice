#include <cmath>
#include <cstdlib>
#include <thread>
#include <sstream>
#include <mutex>

std::mutex mtx;
#include "helpers.h"

using namespace std;

void task2(vector<string> lines){
    bool die = false;
    int pos = -1, oldPos = -1;
    thread menuT (helpers::menu,
            &die);
    while (!die){
        thread t1(helpers::nextPos,
                &pos);
        thread t2(helpers::printLine,
                &pos, oldPos, lines);
        this_thread::sleep_for(chrono::milliseconds(1000));
        t1.join();
        t2.join();
        if (pos == 43){
            pos = -1;
        }
        oldPos = pos;
    }
    menuT.join();
}

int main (void)
{
    vector<string> textLines = helpers::readFileLines
            ("./caged_bird.txt");
    task2(textLines);
    return 0;
}
