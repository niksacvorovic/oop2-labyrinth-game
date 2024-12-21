#pragma once
#include "GameBoard.hpp"

class PowerUp{
    public:
    int duration;
    PowerUp() : duration(3){};
    virtual ~PowerUp() {};
    virtual bool activate(GameBoard& gb, int x, int y)=0;
};

class Mist : public PowerUp{
    public:
    Mist() : PowerUp(){};
    ~Mist() {};
    bool activate(GameBoard& gb, int x, int y) override;
};

class Hammer : public PowerUp{
    public:
    Hammer() : PowerUp(){};
    ~Hammer() {};
    bool activate(GameBoard& gb, int x, int y) override;
};

class Shield : public PowerUp{
    public:
    Shield() : PowerUp(){};
    ~Shield() override {};
    bool activate(GameBoard& gb, int x, int y) override;
};

class Sword : public PowerUp{
    public:
    Sword() : PowerUp(){};
    ~Sword() {};
    bool activate(GameBoard& gb, int x, int y) override;
};

