#include <iostream>
#include "PowerUps.hpp"
#include "GameBoard.hpp"

void Mist::activate(GameBoard& gb){
    std::cout << "Magla\n";
}

void Hammer::activate(GameBoard& gb){
    std::cout << "Cekic\n";
}

void Shield::activate(GameBoard& gb){
    std::cout << "Stit\n";
}

void Sword::activate(GameBoard& gb){
    std::cout << "Mac\n";
}