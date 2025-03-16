#include "StateManager.h"

State StateManager::state = REPOSE;

void StateManager::setState(State state)
{
    StateManager::state = state;
}

State StateManager::getState()
{
    return StateManager::state;
}
