//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_SENSORDATA_H
#define SPIN_SENSORDATA_H


#include <sstream>
#include <iostream>

class SensorData {
/*
 * Sensor data format
 * <Voltage, Ampere, Temp, GyX, GyY, GyZ>
 */

public:
    float voltage;
    float ampere;
    float temp;
    float gyX;
    float gyY;
    float gyZ;


    SensorData()
    {
        voltage = 0.00f;
        ampere = 0.00f;
        temp = 0.00f;
        gyX = 0.00f;
        gyY = 0.00f;
        gyZ = 0.00f;
    }

    void set(const std::string &input)
    {
        // if string is validate assign items to member variables
        if(validate(input))
        {
            std::string newInput = input.substr(1, input.length() - 1); // todo: crap
            int endCharIndex = newInput.find('>');
            newInput = newInput.substr(0, endCharIndex);

            std::stringstream ss(newInput);
            std::string token;
            int argCounter = 1;

            while(std::getline(ss, token, ','))
            {
                switch(argCounter)
                {
                    case 1:
                        voltage = std::stof(token.c_str());
                        break;
                    case 2:
                        ampere = std::stof(token.c_str());
                        break;
                    case 3:
                        temp = std::stof(token.c_str());
                        break;
                    case 4:
                        gyX = std::stof(token.c_str());
                        break;
                    case 5:
                        gyY = std::stof(token.c_str());
                        break;
                    case 6:
                        gyZ = std::stof(token.c_str());
                        break;
                    default:
                        break;
                }
                argCounter++;
            }
        }
        else{
            std::cout << "wrong sensor data: " << input << std::endl;
        }
    }

    // validate function
    bool validate(const std::string &rawInput)
    {
        int endCharIndex = rawInput.find('>');
        std::string input = rawInput.substr(0, endCharIndex+1);

        // check begin and end characters
        if(input[0] != '<' || input[input.length()-1] !='>') return false;

        int commaCounter=0;
        for (int i = 1; i < input.length()-1; ++i) {
            if(input[i]==',') commaCounter++;
        }
        return commaCounter == 5;\
    }

};


#endif //SPIN_SENSORDATA_H
