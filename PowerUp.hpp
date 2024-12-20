#include <iostream>
#include "GameBoard.hpp"

class PowerUp{
    protected:
    int duration;
    public:
    PowerUp() : duration(3){};
    virtual ~PowerUp() {};
    bool decay();
    virtual void activate(GameBoard& gb)=0;
};