#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>

using namespace std;

std::mutex mtx;
std::condition_variable cond_var;

#include "functions.h"

int main(void)
{
    int control_var = (rand() % 4) + 1;
    thread t1(sleep_one, &control_var);
    thread t2(sleep_two, &control_var);
    thread t3(sleep_three, &control_var);
    thread t4(sleep_four, &control_var);

    t1.join();
}