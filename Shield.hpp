#include "PowerUp.hpp"

class Shield : public PowerUp{
    public:
    Shield() : PowerUp(){};
    ~Shield() override {};
    void activate(GameBoard& gb) override;
};