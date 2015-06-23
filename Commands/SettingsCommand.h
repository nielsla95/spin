//
// Created by root on 23-6-15.
//

#ifndef SPIN_SETTINGSCOMMAND_H
#define SPIN_SETTINGSCOMMAND_H


#include "ICommand.h"

class SettingsCommand : public ICommand {

public:
    SettingsCommand(ServoDriver *servoDriver, ControlData *controlData);

    virtual void init() override;

    virtual void run() override;

    std::vector<std::vector<int>> callCSV(std::string initCSV, std::string normalCSV);
};


#endif //SPIN_SETTINGSCOMMAND_H
