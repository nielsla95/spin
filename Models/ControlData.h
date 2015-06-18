//
// Created by root on 11-6-15.
//

#ifndef SPIN_CONTROLDATA_H
#define SPIN_CONTROLDATA_H


#include <sstream>

class ControlData {
/*
 * bluetooth data format
 * <x,y,z,speed,mode,balloon,killswitch>
 * int  mode
 * 0    menu
 * 1    limbo
 * 2    grindbak
 * 3    race
 * 4    dans
 * 5    gap
 * 6    prik
 * 7    paaldans
 * 8    paren
 * 9    settings
 */
public:
    int x;
    int y;
    int z;
    int speed;
    int mode;
    bool killSwitch;
    int balloon; // 0 = niks, 1 = blue

    ControlData() {
        x = 0;
        y = 0;
        z = 0;
        speed = 50;
        mode = 0;
        killSwitch = false;
        balloon = 0;
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
            int m;
            while(std::getline(ss, token, ','))
            {
                switch(argCounter)
                {
                    case 1:
                        x = atoi(token.c_str());
                        break;
                    case 2:
                        y = atoi(token.c_str());
                        break;
                    case 3:
                        z = atoi(token.c_str());
                        break;
                    case 4:
                        speed = atoi(token.c_str());
                        break;
                    case 5:
                        // als settings mode op controller is, zetten we hem hier op mode menu
                        m = atoi(token.c_str());
                        if(m==9)m=0;
                        mode = m;
                        break;
                    case 6:
                        balloon = atoi(token.c_str());
                        break;
                    case 7:
                        killSwitch = (bool)atoi(token.c_str());
                        break;
                    default:
                        break;
                }
                argCounter++;
            }
        }
        else
            std::cout << "wrong bluetooth data: " << input << std::endl;
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
        return commaCounter == 6;
    }

    bool isEqual (ControlData &c1)
    {
        return (x == c1.x &&
                y == c1.y &&
                z == c1.z &&
                mode == c1.mode &&
                killSwitch == c1.killSwitch &&
                balloon == c1.balloon );
    }
    bool isNotEqual (ControlData &c1)
    {
        return !isEqual(c1);
    }

};


#endif //SPIN_CONTROLLERDATA_H
