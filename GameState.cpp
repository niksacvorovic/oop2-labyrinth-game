#include "GameState.hpp"
#include <iostream>
#include <memory>
#include "PowerUps.hpp"

// Funkcija za kretanje igrača
void GameState::player_move(){
    char step;
    bool moves(true);
    int new_x(player_x), new_y(player_y);
    while(moves){
        std::cout << "Unesite korak pomocu tastera W, A, S, D: ";
        std::cin >> step;
        switch(step){
            case 'W':
            case 'w':
            --new_y;
            break;
            case 'A':
            case 'a':
            --new_x;
            break;
            case 'S':
            case 's':
            ++new_y;
            break;
            case 'D':
            case 'd':
            ++new_x;
            break;
            default:
            std::cout << "Neispravan simbol. Pokusajte ponovo\n";
            break;
        }
        // this->activate_powerups();
        if(board[new_y][new_x] != '#' && board[new_y][new_x] != 'U'){
            // if(board[new_y][new_x] == 'P') this->acquire_powerup();
            board[player_y][player_x] = ' ';
            board[new_y][new_x] = 'R';
            player_y = new_y;
            player_x = new_x;
            moves = false;
            if(player_x == enemy_x && player_y == enemy_y) board[new_y][new_x] = 'M';
        }else{
            std::cout << "Ne mozete odigrati ovaj potez\n";
            new_x = player_x;
            new_y = player_y;
        }
    }
}

// Funkcija za kretanje protivnika
void GameState::enemy_move(){
    int random;
    int new_x(enemy_x), new_y(enemy_y);
    if(enemy_x == player_x && abs(enemy_y - player_y) == 1){
        enemy_y = player_y;
        return;
    } 
    if(enemy_y == player_y && abs(enemy_x - player_x) == 1){
        enemy_x = player_x;
        return;
    } 
    
    while(true){
        random = std::rand() % 4;
        switch(random){
            case 0:
            --new_x;
            break;
            case 1:
            --new_y;
            break;
            case 2:
            ++new_x;
            break;
            case 3:
            ++new_y;
            break;
        }
        if(board[new_y][new_x] == ' ' || board[new_y][new_x] == 'P'){
            board[enemy_y][enemy_x] = ' ';
            enemy_x = new_x;
            enemy_y = new_y;
            board[enemy_y][enemy_x] = 'M';
            break;
        }else{
            new_x = enemy_x;
            new_y = enemy_y;
        }
    }
}

// Funkcija za proveru da li je igri došao kraj
bool GameState::game_end(){
    if(board[player_y + 1][player_x] == 'I'){
        std::cout << board;
        std::cout << "Izasli ste iz L A V I R I N T A\n";
        return true;
    }
    if(player_x == enemy_x && player_y == enemy_y){
        std::cout << board;
        std::cout << "Minotaur vas je dokrajcio u L A V I R I N T U\n";
        return true;
    }
    return false;
}

const GameBoard& GameState::get_board(){
    return board;
}

/*void GameBoard::acquire_powerup(){
    int seed = std::rand() % 4;
    std::vector<std::string> names = {"Magla rata", "Cekic", "Stit", "Mac"};
    for(auto it = powerups.begin(); it != powerups.end(); it++){
        if((**it).type == seed){
            (**it).duration += 3;
            std::cout << "Dobijate jos tri poteza sledeceg efekta " << names[seed] << '\n';
            return;
        }
    }
    PowerUp* ptr;
    switch(seed){
        case 0:
        ptr = new Mist();
        std::cout << names[seed] << " - sledeca tri poteza vidite samo jedno polje oko sebe\n";
        break;
        case 1:
        ptr = new Hammer();
        std::cout << names[seed] << " - sledeca tri poteza mozete da probijate zidove\n";
        break;
        case 2:
        std::cout << names[seed] << " - sledeća tri poteza se mozete odbraniti od Minotaura\n";
        ptr = new Shield();
        break;
        case 3:
        std::cout << names[seed] << " - sledeća tri poteza mozete dokrajciti Minotaura!\n";
        ptr = new Sword();
        break;
    }
    powerups.push_back(ptr);
}

// void GameBoard::acquire_powerup(){
//     int seed = std::rand() % 4;
//     std::unique_ptr<PowerUp> ptr;
//     switch(seed){
//         case 0:
//         ptr = std::unique_ptr<Mist>(new Mist());
//         break;
//         case 1:
//         ptr = std::unique_ptr<Hammer>(new Hammer());
//         break;
//         case 2:
//         ptr = std::unique_ptr<Shield>(new Shield());
//         break;
//         case 3:
//         ptr = std::unique_ptr<Sword>(new Sword());
//         break;
//     }
//     // koristimo emplace_back zato što ne dodajemo kopiju u vektor, već pomeramo postojeći objekat
//     powerups.emplace_back(ptr);
// }

void GameBoard::activate_powerups(){
    auto it = powerups.begin();
    while(it != powerups.end()){
        // prvom zvedzicom derefrenciramo iterator a drugom pokazivač
        //(**it).activate(*this);
        --(**it).duration;
        if((**it).duration == 0){
            std::cout << "Isteklo\n";
            delete *it;
            it = powerups.erase(it);
        } else {
            ++it;
        }
    }
}*/