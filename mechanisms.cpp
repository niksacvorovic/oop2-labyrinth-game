#include "GameBoard.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Mehanizmi za funkcionisanje igrice

// Algoritam za generisanje lavirinta
void GameBoard::initialize(){
    char** newboard = new char* [height];
    for(int i = 0; i < height; ++i){
        newboard[i] = new char[width];
    }
    std::time_t seed = std::time(0);
    std::srand(seed);
    player_y = 1;
    player_x = (std::rand() % (width - 2)) + 1;
    enemy_y = height - 2;
    enemy_x = (std::rand() % (width - 2)) + 1;
    for(int i = 0; i < width; ++i){
        if (i == player_x){
            newboard[0][i] = 'U';
        }else{
            newboard[0][i] = '#';
        }
        if (i == enemy_x){
            newboard[width - 1][i] = 'I';
        }else{
            newboard[width - 1][i] = '#';
        }
    }
    for(int i = 1; i < height - 1; ++i){
        for(int j = 0; j < width; ++j){
            if(j == 0 || j == width - 1){
                newboard[i][j] = '#';
            }else{
                newboard[i][j] = ' ';
            }
        }
    }
    newboard[player_y][player_x] = 'R';
    newboard[enemy_y][enemy_x] = 'M';
    board = newboard;
    double passtime = std::difftime(std::time(0), seed);
    std::cout << passtime << '\n';
}

// Funkcije za kretanje igrača
void GameBoard::player_move(){
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
        if(new_x >= 0 && new_x <= width - 1 && new_y >= 0 && new_y <= height - 1 && board[new_y][new_x] != '#'){
            board[player_y][player_x] = ' ';
            board[new_y][new_x] = 'R';
            player_y = new_y;
            player_x = new_x;
            moves = false;
        }else{
            std::cout << "Ne možete odigrati ovaj potez";
            new_x = player_x;
            new_y = player_y;
        }
    }
}

// Funkcija za kretanje protivnika
void GameBoard::enemy_move(){
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
        }
    }
}

// Funkcija za proveru da li je igri došao kraj
bool GameBoard::game_end(){
    if(board[player_y + 1][player_x] == 'I'){
        std::cout << *this;
        std::cout << "Izasli ste iz L A V I R I N T A\n";
        return true;
    }
    if(player_x == enemy_x && player_y == enemy_y){
        std::cout << *this;
        std::cout << "Minotaur vas je dokrajcio u L A V I R I N T U\n";
        return true;
    }
    return false;
}