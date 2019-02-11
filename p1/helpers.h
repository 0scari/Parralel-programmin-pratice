//
// Created by Oskars Pozdnakovs on 2019-02-02.
//

#ifndef P1_HELPERS_H
#define P1_HELPERS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

namespace helpers {

    vector<string> readFileLines(string filename)
    {
        ifstream file(filename);
        vector<string> textLines = {"\n"};
        string line;
        if(file.is_open()){
            while (getline(file, line)){
                line.pop_back();
                textLines.push_back(line);
            }
        }
        return textLines;
    }

    void printLine(int *pos, int oldPos, vector<string> lines)
    {
        if (*pos > oldPos) {
            mtx.lock();
            cout << lines[*pos] << endl;
            mtx.unlock();
        } else {
            this_thread::sleep_for(chrono::milliseconds(100));
        }

    }

    void nextPos(int *pos)
    {
        mtx.lock();
        (*pos)++;
        mtx.unlock();
    }


    void menu(bool *die)
    {
        string inp;
        bool locked = false;
        cout << "[p+enter]: pause, [r+enter]: resume, [e+enter]: exit "
             << "// both keys must be pressed while on the same line" << endl;
        do {
            getline(cin, inp);
            if (inp == "p" && !locked){
                mtx.lock();
                locked = true;
            }
            if (inp == "r" && locked){
                mtx.unlock();
                locked = false;
                cin.clear();
            }
        } while(inp != "e");
        *die = true;
        if (locked)
            mtx.unlock();
    }
}

#endif //P1_HELPERS_H
