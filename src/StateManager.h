enum State
{
    REPOSE,
    CALIBRATE,
    CONFIGURE,
    READING
};

class StateManager
{
private:
    State state = REPOSE;

public:
    void setState(State state);
    State getState();
};
