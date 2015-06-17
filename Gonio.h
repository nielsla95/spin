//
// Created by root on 16-6-15.
//

#ifndef SPIN_GONIO_H
#define SPIN_GONIO_H
#include <string>
#include <vector>
#include <math.h>
#include <iostream>

class Gonio {
private:
public:
    std::vector<float> results;
    Gonio(std::string file) {

        std::string test = "csv/" + file;
        // read CSV file to float vector
        results = readCSV(test);
        // read float vector covert to double int vector
        std::vector<std::vector<int>> validVars = calcVars();

        // RESULTS PRINTED HUR
        printResults(validVars);
    }

    virtual ~Gonio() { }

    std::vector<float> readCSV(std::string fileName);
    std::vector<std::vector<int>> calcVars();

    float toDegree(float rad);
    int mapToServo(float input);

    // for testing purposes
    void printResults(std::vector<std::vector<int>> validVars);
};

#endif //SPIN_GONIO_H
