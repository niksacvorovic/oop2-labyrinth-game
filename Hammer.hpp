#include "PowerUp.hpp"

class Hammer : public PowerUp{
    public:
    Hammer() : PowerUp(){};
    ~Hammer() {};
    void activate(GameBoard& gb) override;
};