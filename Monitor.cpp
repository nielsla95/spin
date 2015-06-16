//
// Created by eele on 9-6-2015.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include "Monitor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

#define BAUDRATE B9600
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */



void Monitor::listen(SensorData &sensorData)
{
    bool stop=false;
    int fd,c, len;
    struct termios oldtio,newtio;
    char buf[2048];
    len = 0;
    std::string output="";

    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
    if (fd <0)
    {
        perror(MODEMDEVICE); return listen(sensorData);
    }

    tcgetattr(fd,&oldtio); /* save current port settings */

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);

    while (true) {       /* loop for input */
        len = read(fd, buf, sizeof(buf));   /* returns after 5 chars have been input */
        buf[len] = 0;
        output += buf;

        std::string fix = "";

        int finalCommandIndex = 0;
        for(int  i = 0; i < output.length(); i++)
        {
            if(output[i] == '<')
                finalCommandIndex = i;
        }

        fix = output.substr(finalCommandIndex, output.length() - finalCommandIndex);

//        std::cout << buf << std::endl;
//        std::cout << "Nieuw" << std::endl;
//        std::cout << fix << std::endl;

        sensorData.set(fix);
        usleep(1000000);
        output = "";
        if (fd <0)
        {
            perror(MODEMDEVICE); return listen(sensorData);
        }
    }
}