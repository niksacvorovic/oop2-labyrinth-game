#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include "GameState.hpp"

/*  Projekat iz predmeta Objektno orijentisano programiranje 2 - lavirint igra 
    Struktura projekta
    - main.cpp - glavna funkcija programa
    - GameState.hpp, GameState.cpp - implementacija stanja igre
    - GameBoard.hpp, GameState.cpp - implementacija table za igru
    - PowerUps.hpp, PowerUp.cpp - implementacija specijalnih efekata
    Za istoriju verzija konsultovati se sa GitHub repozitorijumom na sledećem linku
    https://github.com/niksacvorovic/oop2-labyrinth-game
*/

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
    int seed = std::time(0);
    std::srand(seed);
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