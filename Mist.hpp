#include "PowerUp.hpp"

class Mist : public PowerUp{
    public:
    Mist() : PowerUp(){};
    ~Mist() {};
    void activate(GameBoard& gb) override;
};