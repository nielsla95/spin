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

    bool isEqual (ControlData &c1)
    {
        return (x == c1.x &&
                y == c1.y &&
                z == c1.z &&
                speed == c1.speed &&
                mode == c1.mode &&
                killSwitch == c1.killSwitch &&
                balloon == c1.balloon );
    }
    bool isNotEqual (ControlData &c1)
    {
        return !isEqual(c1);
    }

    void set(int x, int y, int z, int speed, int mode, bool killSwitch, int balloon){
        setJoystick(x,y);
        std::cout << "set: " << mode << std::endl;
        setRest(z,speed,mode,killSwitch,balloon);
    }

    void setJoystick(int _x, int _y)
    {
        x=_x;
        y=_y;

        //std::cout << "X: " << x << " Y: " <<y<<std::endl;
    }

    void setRest(int _z, int _speed, int _mode, bool _killSwitch, int _balloon)
    {
        z=_z;
        speed = _speed;
        mode = _mode;
        // todo: mode kijken
        killSwitch = _killSwitch;
        balloon=_balloon;
        std::cout << "setRest: " << mode << std::endl;
    }

};


#endif //SPIN_CONTROLLERDATA_H
