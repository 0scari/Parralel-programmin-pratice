//
// Created by Oskars Pozdnakovs on 2019-02-02.
//

#ifndef P1_HELPERS_H
#define P1_HELPERS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace helpers {

    std::vector<std::string> readFileLines(std::string filename)
    {
        std::ifstream file(filename);
        std::vector<std::string> textLines = {"\n"};
        std::string line;
        if(file.is_open()){
            while (getline(file, line)){
                line.pop_back();
                textLines.push_back(line);
            }
        }
        return textLines;
    }

    void printLine(int *pos, int oldPos, std::vector<std::string> lines)
    {
        if (*pos > oldPos) {
            mtx.lock();
            std::cout << lines[*pos] << std::endl;
            mtx.unlock();
        } else {
            printLine(pos, oldPos, lines);
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
        int ch;
        bool locked = false;
        do {
            ch = std::cin.get();
            if (ch == 'p'){
                mtx.lock();
                locked = true;
            }
            if (ch == 'r' && locked){
                mtx.unlock();
                locked = false;
                std::cin.clear();
            }
        } while(ch != 'e');
        *die = true;

    }
}

#endif //P1_HELPERS_H
