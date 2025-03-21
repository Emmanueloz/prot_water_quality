#include "StateManager.h"

State StateManager::_state = INITIALIZE;

void StateManager::setState(State state)
{
    StateManager::_state = state;
}

State StateManager::getState()
{
    return StateManager::_state;
}

String StateManager::getStateString()
{
    switch (StateManager::getState())
    {
    case INITIALIZE:
        return "INITIALIZE";
    case REPOSE:
        return "REPOSE";
    case CALIBRATE:
        return "CALIBRATE";
    case CONFIGURE:
        return "CONFIGURE";
    case READING:
        return "READING";
    default:
        return "UNKNOWN";
    }
}
