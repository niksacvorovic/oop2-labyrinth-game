#include <iostream>
#include <string>
#include "GameState.hpp"

int main(int argc, char* argv[]){
    // Obrada argumenata komandne linije
    int dim_1, dim_2, item_count;
    try{
        dim_1 = std::stoi(argv[1]);
        dim_2 = std::stoi(argv[2]);
        item_count = std::stoi(argv[3]);
    } catch (std::invalid_argument& e){
        std::cerr << "Neispravan unos!\n";
        return -1;
    }
    if(dim_1 < 15 || dim_2 < 15 || item_count < 3){
        std::cout << "Nedovoljno veliki unos!\n";
        return -1;
    }
    std::cout << "Dobrodosli u L A V I R I N T\n";
    // Generisanje table
    GameState g(dim_1, dim_2, item_count);
    // Gameplay petlja
    do{
        g.print_board();
        g.player_move();
        if(g.game_end()) break;
        g.enemy_move();
    }while(!g.game_end());
    // Ispis u fajl
    g.output_board();
    return 0;
}