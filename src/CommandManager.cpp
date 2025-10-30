#include "CommandManager.h"

Command CommandManager::getCommand()
{
    String command = Serial.readStringUntil('\n');
    command.trim();
    int separator = command.indexOf(':');
    String commandName = command.substring(0, separator);
    String commandValue = command.substring(separator + 1);

    Command commandStruct;
    commandStruct.name = commandName;
    commandStruct.value = commandValue;
    return commandStruct;
}
