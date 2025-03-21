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
