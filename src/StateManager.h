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
    static State state;

public:
    static void setState(State state);
    static State getState();
};
