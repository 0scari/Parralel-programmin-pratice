//
// Created by Oskars Pozdnakovs on 2019-02-11.
//

#ifndef P3_FUNCTIONS_H
#define P3_FUNCTIONS_H

void sleep(int *control_var, unique_lock<mutex>& lk)
{
    cout << "😴 Thread " << *control_var << " has drifted off" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "😳 Thread " << *control_var << " woke up" << endl;
    *control_var = rand() % 4 + 1;
    lk.unlock();
    cond_var.notify_all();
}

void sleep_one (int *control_var)
{
    while(true){
        unique_lock<std::mutex> lck(mtx);
        cond_var.wait(lck, [control_var]{return *control_var == 1;});
        sleep(control_var, lck); 
    }
};
void sleep_two (int *control_var)
{
    while(true){
        unique_lock<std::mutex> lck(mtx);
        cond_var.wait(lck, [control_var]{return *control_var == 2;});
        sleep(control_var, lck); 
    }
};
void sleep_three (int *control_var)
{
    while(true){
        unique_lock<std::mutex> lck(mtx);
        cond_var.wait(lck, [control_var]{return *control_var == 3;});
        sleep(control_var, lck); 
    }
};
void sleep_four (int *control_var)
{
    while(true){
        unique_lock<std::mutex> lck(mtx);
        cond_var.wait(lck, [control_var]{return *control_var == 4;});
        sleep(control_var, lck); 
    }
};

#endif //P3_FUNCTIONS_H
