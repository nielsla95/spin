//
// Created by root on 16-6-15.
//

#include "Gonio.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>

/* CSV File format
 * p1    p2    z5    p4    p5    p6
 * x,y,z,x,y,z,x,y,z,x,y,z,x,y,z,x,y,z
 * x,y,z,x,y,z,x,y,z,x,y,z,x,y,z,x,y,z
 * x,y,z,x,y,z,x,y,z,x,y,z,x,y,z,x,y,z
 * etc
 */

std::vector<float> Gonio::readCSV(std::string fileName) {

    std::string lineBuffer;
    std::string input;
    std::vector<float> vars;

    // read file
    std::ifstream infile(fileName);
    // momenteel bij run config een working directory van deze map ingesteld
    if(infile){
        // Laat zien welk bestandje hij leest
        std::cout << "Reading: " << fileName << std::endl;


        while (!infile.eof()) // To get you all the lines.
        {
            std::getline(infile, lineBuffer); // Saves the line in STRING.
            input += lineBuffer;
            input += ",";
        }
        infile.close();

        std::string buffer = "";

        int inputCounter=0;
        for (int j = 0; j < input.size(); ++j) {
            if (input[j] == ',' || j == input.size()) {

                if(buffer.length() > 0)
                {
                    inputCounter++;
                    //std::cout << "testoutput "<< inputCounter << " :" << buffer << std::endl;
                    vars.push_back(std::stof(buffer.c_str()));
                }

                buffer = "";
            } else {
                buffer += input[j];
            }
        }
    }else{
        std::cout << "Can't find file: " << fileName << std::endl;
    }
    return vars;
}

float Gonio::toDegree(float rad) {
    // floor and + 0.5f makes converting to int better
    return rad*(180/M_PI);
}

std::vector<std::vector<int>> Gonio::calcVars() {
    std::vector<float> input = results;
    std::vector<std::vector<int>> result;
    std::vector<int> buffer;

    float Lc=68;
    float Lf=137.8f;
    float Lt=164.37f;

    // results for each leg
    float C1,F1,T1;
    float C2,F2,T2;
    float C3,F3,T3;
    float C4,F4,T4;
    float C5,F5,T5;
    float C6,F6,T6;

    float x1,x2,x3,x4,x5,x6;
    float y1,y2,y3,y4,y5,y6;
    float z1,z2,z3,z4,z5,z6;

    for (int i = 0; i < input.size()/18; ++i) {
        x1 = input.at(0+18*i);//b
        y1 = input.at(1+18*i);//c
        z1 = input.at(2+18*i);//d
        x2 = input.at(3+18*i);//e
        y2 = input.at(4+18*i);//f
        z2 = input.at(5+18*i);//g
        x3 = input.at(6+18*i);//h
        y3 = input.at(7+18*i);//i
        z3 = input.at(8+18*i);//j
        x4 = input.at(9+18*i);//k
        y4 = input.at(10+18*i);//l
        z4 = input.at(11+18*i);//m
        x5 = input.at(12+18*i);//n
        y5 = input.at(13+18*i);//o
        z5 = input.at(14+18*i);//p
        x6 = input.at(15+18*i);//q
        y6 = input.at(16+18*i);//r
        z6 = input.at(17+18*i);//s

        // GOED
        C1 = 150-(toDegree(atan(y1/x1)));
        // GOED
        F1 = 150-(90-((toDegree(atan(((sqrt((x1*x1)+(y1*y1)))-Lc)/-z1)))+(toDegree(acos(((Lt*Lt)-(Lf*Lf)-(sqrt((((sqrt((x1*x1)+(y1*y1)))-(Lc))*((sqrt((x1*x1)+(y1*y1)))-(Lc)))+(z1*z1)))*(sqrt((((sqrt((x1*x1)+(y1*y1)))-(Lc))*((sqrt((x1*x1)+(y1*y1)))-(Lc)))+(z1*z1))))/(-2*(Lf)*(sqrt((((sqrt((x1*x1)+(y1*y1)))-(Lc))*((sqrt((x1*x1)+(y1*y1)))-(Lc)))+(z1*z1)))))))));
        // GOED
        T1 = 150+(180-(toDegree(acos((((sqrt((sqrt((x1*x1)+(y1*y1))-Lc)*(sqrt((x1*x1)+(y1*y1))-Lc)+(z1*z1)))*(sqrt((sqrt((x1*x1)+(y1*y1))-Lc)*(sqrt((x1*x1)+(y1*y1))-Lc)+(z1*z1))))-(Lt*Lt)-(Lf*Lf))/(-2*Lt*Lf)))));

        C2 =(150-27.27)-(toDegree(atan(y2/x2)));
        F2 = F2 =150-(90-((toDegree(atan(((sqrt((x2*x2)+(y2*y2)))-Lc)/-z2)))+(toDegree(acos(((Lt*Lt)-(Lf*Lf)-(sqrt((((sqrt((x2*x2)+(y2*y2)))-(Lc))*((sqrt((x2*x2)+(y2*y2)))-(Lc)))+(z2*z2)))*(sqrt((((sqrt((x2*x2)+(y2*y2)))-(Lc))*((sqrt((x2*x2)+(y2*y2)))-(Lc)))+(z2*z2))))/(-2*(Lf)*(sqrt((((sqrt((x2*x2)+(y2*y2)))-(Lc))*((sqrt((x2*x2)+(y2*y2)))-(Lc)))+(z2*z2)))))))));;
        // GOED
        T2 = 150+(180-(toDegree(acos((((sqrt((sqrt((x2*x2)+(y2*y2))-Lc)*(sqrt((x2*x2)+(y2*y2))-Lc)+(z2*z2)))*(sqrt((sqrt((x2*x2)+(y2*y2))-Lc)*(sqrt((x2*x2)+(y2*y2))-Lc)+(z2*z2))))-(Lt*Lt)-(Lf*Lf))/(-2*Lt*Lf)))));

        C3 =150-(toDegree(atan(y3/x3)));
        F3 =150-(90-((toDegree(atan(((sqrt((x3*x3)+(y3*y3)))-Lc)/-z3)))+(toDegree(acos(((Lt*Lt)-(Lf*Lf)-(sqrt((((sqrt((x3*x3)+(y3*y3)))-(Lc))*((sqrt((x3*x3)+(y3*y3)))-(Lc)))+(z3*z3)))*(sqrt((((sqrt((x3*x3)+(y3*y3)))-(Lc))*((sqrt((x3*x3)+(y3*y3)))-(Lc)))+(z3*z3))))/(-2*(Lf)*(sqrt((((sqrt((x3*x3)+(y3*y3)))-(Lc))*((sqrt((x3*x3)+(y3*y3)))-(Lc)))+(z3*z3)))))))));
        T3=150+(180-(toDegree(acos((((sqrt((sqrt((x3*x3)+(y3*y3))-Lc)*(sqrt((x3*x3)+(y3*y3))-Lc)+(z3*z3)))*(sqrt((sqrt((x3*x3)+(y3*y3))-Lc)*(sqrt((x3*x3)+(y3*y3))-Lc)+(z3*z3))))-(Lt*Lt)-(Lf*Lf))/(-2*Lt*Lf)))));

        C4=150+(toDegree(atan(y4/x4)));
        F4=150+(90-((toDegree(atan(((sqrt((x4*x4)+(y4*y4)))-Lc)/-z4)))+(toDegree(acos(((Lt*Lt)-(Lf*Lf)-(sqrt((((sqrt((x4*x4)+(y4*y4)))-(Lc))*((sqrt((x4*x4)+(y4*y4)))-(Lc)))+(z4*z4)))*(sqrt((((sqrt((x4*x4)+(y4*y4)))-(Lc))*((sqrt((x4*x4)+(y4*y4)))-(Lc)))+(z4*z4))))/(-2*(Lf)*(sqrt((((sqrt((x4*x4)+(y4*y4)))-(Lc))*((sqrt((x4*x4)+(y4*y4)))-(Lc)))+(z4*z4)))))))));
        T4=150+(180-(toDegree(acos((((sqrt((sqrt((x4*x4)+(y4*y4))-Lc)*(sqrt((x4*x4)+(y4*y4))-Lc)+(z4*z4)))*(sqrt((sqrt((x4*x4)+(y4*y4))-Lc)*(sqrt((x4*x4)+(y4*y4))-Lc)+(z4*z4))))-(Lt*Lt)-(Lf*Lf))/(-2*Lt*Lf)))));

        C5=(150-27.27)+(toDegree(atan(y5/x5)));
        F5=150+(90-((toDegree(atan(((sqrt((x5*x5)+(y5*y5)))-Lc)/-z5)))+(toDegree(acos(((Lt*Lt)-(Lf*Lf)-(sqrt((((sqrt((x5*x5)+(y5*y5)))-(Lc))*((sqrt((x5*x5)+(y5*y5)))-(Lc)))+(z5*z5)))*(sqrt((((sqrt((x5*x5)+(y5*y5)))-(Lc))*((sqrt((x5*x5)+(y5*y5)))-(Lc)))+(z5*z5))))/(-2*(Lf)*(sqrt((((sqrt((x5*x5)+(y5*y5)))-(Lc))*((sqrt((x5*x5)+(y5*y5)))-(Lc)))+(z5*z5)))))))));
        T5=150+(180-(toDegree(acos((((sqrt((sqrt((x5*x5)+(y5*y5))-Lc)*(sqrt((x5*x5)+(y5*y5))-Lc)+(z5*z5)))*(sqrt((sqrt((x5*x5)+(y5*y5))-Lc)*(sqrt((x5*x5)+(y5*y5))-Lc)+(z5*z5))))-(Lt*Lt)-(Lf*Lf))/(-2*Lt*Lf)))));

        C6=150+(toDegree(atan(y6/x6)));
        F6=150+(90-((toDegree(atan(((sqrt((x6*x6)+(y6*y6)))-Lc)/-z6)))+(toDegree(acos(((Lt*Lt)-(Lf*Lf)-(sqrt((((sqrt((x6*x6)+(y6*y6)))-(Lc))*((sqrt((x6*x6)+(y6*y6)))-(Lc)))+(z6*z6)))*(sqrt((((sqrt((x6*x6)+(y6*y6)))-(Lc))*((sqrt((x6*x6)+(y6*y6)))-(Lc)))+(z6*z6))))/(-2*(Lf)*(sqrt((((sqrt((x6*x6)+(y6*y6)))-(Lc))*((sqrt((x6*x6)+(y6*y6)))-(Lc)))+(z6*z6)))))))));
        T6=150+(180-(toDegree(acos((((sqrt((sqrt((x6*x6)+(y6*y6))-Lc)*(sqrt((x6*x6)+(y6*y6))-Lc)+(z6*z6)))*(sqrt((sqrt((x6*x6)+(y6*y6))-Lc)*(sqrt((x6*x6)+(y6*y6))-Lc)+(z6*z6))))-(Lt*Lt)-(Lf*Lf))/(-2*Lt*Lf)))));

        buffer.push_back(mapToServo(C1));
        buffer.push_back(mapToServo(F1));
        buffer.push_back(mapToServo(T1));
        buffer.push_back(mapToServo(C2));
        buffer.push_back(mapToServo(F2));
        buffer.push_back(mapToServo(T2));
        buffer.push_back(mapToServo(C3));
        buffer.push_back(mapToServo(F3));
        buffer.push_back(mapToServo(T3));
        buffer.push_back(mapToServo(C4));
        buffer.push_back(mapToServo(F4));
        buffer.push_back(mapToServo(T4));
        buffer.push_back(mapToServo(C5));
        buffer.push_back(mapToServo(F5));
        buffer.push_back(mapToServo(T5));
        buffer.push_back(mapToServo(C6));
        buffer.push_back(mapToServo(F6));
        buffer.push_back(mapToServo(T6));

        result.push_back(buffer);
        buffer.clear();
    }

    return result;
}

int Gonio::mapToServo(float input) {
    int result = floor((3.41*input)+0.5f);
    if(result>1023 || result < 0)
    {
        while(true) {
            std::cout << "MAPPING HIGHER OR LOWER THAN 1023. Input: " << input << " output: " << result << std::endl;
            usleep(10000000);
        }
    }
    return result;
}


void Gonio::printResults(std::vector<std::vector<int>> validVars) {
    for (int i = 0; i < validVars.size(); ++i) {
        for (int j = 0; j < validVars.at(i).size(); ++j) {
            std::cout << " -> " << validVars.at(i).at(j);
        }
        std::cout << std::endl;
    }
}
