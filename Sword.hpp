#include "PowerUp.hpp"

class Sword : public PowerUp{
    public:
    Sword() : PowerUp(){};
    ~Sword() {};
    void activate(GameBoard& gb) override;
};