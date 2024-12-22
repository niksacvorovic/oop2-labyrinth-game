#pragma once
#include "GameBoard.hpp"

// Klase za reprezentaciju specijalnih predmeta i njihovih efekata
// Sadrže brojač trajnosti i virtuelni poziv njihovog efekta
class PowerUp{
    public:
    int duration;
    PowerUp(int d) : duration(d){};
    virtual ~PowerUp() {};
    virtual bool activate(GameBoard& gb, int x, int y)=0;
};

class Mist : public PowerUp{
    public:
    Mist() : PowerUp(3){};
    ~Mist() {};
    bool activate(GameBoard& gb, int x, int y) override;
};

class Hammer : public PowerUp{
    public:
    Hammer() : PowerUp(3){};
    ~Hammer() {};
    bool activate(GameBoard& gb, int x, int y) override;
};

// Pošto predmeti gube jedan bod trajanja pre poteza igrača mač i štit imaju inicijalizovano trajanje 4
class Shield : public PowerUp{
    public:
    Shield() : PowerUp(4){};
    ~Shield() override {};
    bool activate(GameBoard& gb, int x, int y) override;
};

class Sword : public PowerUp{
    public:
    Sword() : PowerUp(4){};
    ~Sword() {};
    bool activate(GameBoard& gb, int x, int y) override;
};

