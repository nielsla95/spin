//
// Created by eele on 9-6-2015.
//

#ifndef SPIN_SENSORDATA_H
#define SPIN_SENSORDATA_H


#include <sstream>

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
        std::string testData = "<1,2.00,34,5,6,7.00>";
        set(testData);
    }

    void set(const std::string &input)
    {
        // if string is validate assign items to member variables
        if(validate(input))
        {
            std::string newInput = input; // todo: comment hier onder verwijderen als het niet meer nodig is
            //std::string newInput = input.substr(1, input.length() - 2);
            std::stringstream ss(newInput);
            std::string token;
            int argCounter = 1;

            while(std::getline(ss, token, ','))
            {
                switch(argCounter)
                {
                    case 1:
                        voltage = atof(token.c_str());
                        break;
                    case 2:
                        ampere = atof(token.c_str());
                        break;
                    case 3:
                        temp = atof(token.c_str());
                        break;
                    case 4:
                        gyX = atof(token.c_str());
                        break;
                    case 5:
                        gyY = atof(token.c_str());
                        break;
                    case 6:
                        gyZ = atof(token.c_str());
                        break;
                    default:
                        break;
                }
                argCounter++;
            }
        }
        else
            std::cout << "wrong sensor data: " << input << std::endl;
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
        return commaCounter == 5;
        return false;
    }

};


#endif //SPIN_SENSORDATA_H
