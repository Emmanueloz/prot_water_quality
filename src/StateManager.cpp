#include "StateManager.h"

State StateManager::_state = CONFIGURE;

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
    case CONFIGURE:
        return "CONFIGURE";
    case READING:
        return "READING";
    default:
        return "UNKNOWN";
    }
}
