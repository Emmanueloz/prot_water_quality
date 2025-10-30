#include <Arduino.h>
#pragma once

struct Command
{
    String name;
    String value;
};

class CommandManager
{
public:
    static Command getCommand();
};
