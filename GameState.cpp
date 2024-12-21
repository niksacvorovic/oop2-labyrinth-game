#include "GameState.hpp"
#include <iostream>
#include <memory>
#include "PowerUps.hpp"

GameState::~GameState(){
    for(PowerUp* powerup : powerups) delete powerup;
}

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
            case 'Q':
            case 'q':
            exit(0);
            default:
            std::cout << "Neispravan simbol. Pokusajte ponovo\n";
            break;
        }
        if((activate_powerup(1, new_x, new_y) || board[new_y][new_x] != '#') && board[new_y][new_x] != 'U'){
            decay_powerups();
            if(board[new_y][new_x] == 'P') acquire_powerup();
            board[player_y][player_x] = ' ';
            board[new_y][new_x] = 'R';
            player_y = new_y;
            player_x = new_x;
            moves = false;
            // Predmete pozivamo jednom po potezu - zato ovom konstrukcijom pozivamo mač
            bool kill_minotaur = activate_powerup(3, player_x, player_y);
            if(player_x == enemy_x && player_y == enemy_y){
                if(kill_minotaur){
                    enemy_x = 0;
                    enemy_y = 0;
                }else board[player_y][player_x] = 'M';
            }
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
    // Minotaur se neće kretati ako je dokrajčen
    if(enemy_x == 0 && enemy_y == 0){
        return;
    }
    if(enemy_x == player_x && abs(enemy_y - player_y) == 1 && !activate_powerup(2, 0, 0)){
        enemy_y = player_y;
        return;
    } 
    if(enemy_y == player_y && abs(enemy_x - player_x) == 1 && !activate_powerup(2, 0, 0)){
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

void GameState::print_board(){
    if(!activate_powerup(0, player_x, player_y)) std::cout << board;
}

void GameState::acquire_powerup(){
    int seed = std::rand() % 4;
    std::vector<std::string> names = {"Magla rata", "Cekic", "Stit", "Mac"};
    if(powerups[seed] != nullptr) {
        (*(powerups[seed])).duration += 3;
        std::cout << "Dobijate jos tri poteza sledeceg efekta: " << names[seed] << '\n';
    } else {
        switch(seed){
        case 0:
        powerups[0] = new Mist();
        std::cout << names[seed] << " - sledeca tri poteza vidite samo jedno polje oko sebe\n";
        break;
        case 1:
        powerups[1] = new Hammer();
        std::cout << names[seed] << " - sledeca tri poteza mozete da probijate zidove\n";
        break;
        case 2:
        powerups[2] = new Shield();
        std::cout << names[seed] << " - sledeca tri poteza se mozete odbraniti od Minotaura\n";
        break;
        case 3:
        powerups[3] = new Sword();
        std::cout << names[seed] << " - sledeca tri poteza mozete dokrajciti Minotaura!\n";
        break;
        }
    }
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

bool GameState::activate_powerup(int index, int x, int y){
    bool activated(false);
    if (powerups[index] != nullptr){
        activated = powerups[index]->activate(board, x, y);
    }
    return activated;
}

void GameState::decay_powerups(){
    for(auto& powerup : powerups){
        if(powerup != nullptr){
            --powerup->duration;
            if(powerup->duration == 0) powerup = nullptr;
        }
    }
}