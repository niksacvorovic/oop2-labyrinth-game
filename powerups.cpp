#include <iostream>
#include "PowerUps.hpp"
#include "GameBoard.hpp"

bool Mist::activate(GameBoard& gb, int x, int y){
    for(int j = 0; j < gb.get_height(); ++j){
        for(int i = 0; i < gb.get_width(); ++i){
            if(i >= x - 1 && i <= x + 1 && j >= y - 1 && j <= y + 1) std::cout << gb[j][i] << ' ';
            else std::cout << '~' << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Magla rata ce trajati " << duration << " poteza\n";
    return true;
}

bool Hammer::activate(GameBoard& gb, int x, int y){
    if(duration == 1){
        std::cout << "Cekic je istekao!\n";
    } else {
        std::cout << "Cekic mozete koristiti " << duration - 1 << " poteza\n";
    }
    return gb[y][x] == '#' && x != 0 && y != 0 && x != gb.get_width() - 1 && y != gb.get_height() - 1;
}

bool Shield::activate(GameBoard& gb, int x, int y){
    std::cout << "Stit vam traje jos " << duration - 1 << " poteza\n";
    return true;
}

bool Sword::activate(GameBoard& gb, int x, int y){
    if(duration == 1){
        std::cout << "Mac je istekao!\n";
    } else {
        std::cout << "Mac mozete koristiti " << duration - 1 << " poteza\n";
    }
    return gb[y][x] == 'M';
}