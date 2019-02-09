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
        std::vector<std::string> textLines;
        std::string line;
        if(file.is_open()){
            while (getline(file, line)){
                textLines.push_back(line);
            }
        }
        return textLines;
    }

    void printLine(int pos, std::vector<std::string> lines)
    {
        std::cout << lines[pos] << std::endl;
    }

    void nextPos(int *pos)
    {
        (*pos)++;
    }

}

#endif //P1_HELPERS_H
