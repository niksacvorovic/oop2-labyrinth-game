#pragma once
#include "GameBoard.hpp"

class PowerUp{
    public:
    int duration, type;
    PowerUp(int t) : duration(3), type(t){};
    virtual ~PowerUp() {};
    virtual void activate(GameBoard& gb)=0;
};

class Mist : public PowerUp{
    public:
    Mist() : PowerUp(0){};
    ~Mist() {};
    void activate(GameBoard& gb) override;
};

class Hammer : public PowerUp{
    public:
    Hammer() : PowerUp(1){};
    ~Hammer() {};
    void activate(GameBoard& gb) override;
};

class Shield : public PowerUp{
    public:
    Shield() : PowerUp(2){};
    ~Shield() override {};
    virtual void activate(GameBoard& gb) override;
};

class Sword : public PowerUp{
    public:
    Sword() : PowerUp(3){};
    ~Sword() {};
    virtual void activate(GameBoard& gb) override;
};

