#include "GameBoard.h"
#include <cstdlib>
#include <ctime>
#include <set>

// Generisanje ulaza, izlaza i spoljašnjih zidova
void GameBoard::generate_outer_walls(){
    int seed = std::time(0);
    std::srand(seed);
    player_y = 1;
    player_x = (std::rand() % (width - 2)) + 1;
    enemy_y = height - 2;
    enemy_x = (std::rand() % (width - 2)) + 1;
    for(int i = 0; i < width; ++i){
        if (i == player_x){
            board[0][i] = 'U';
        }else{
            board[0][i] = '#';
        }
        if (i == enemy_x){
            board[width - 1][i] = 'I';
        }else{
            board[width - 1][i] = '#';
        }
    }
    for(int i = 1; i < height - 1; ++i){
        for(int j = 0; j < width; ++j){
            if(j == 0 || j == width - 1){
                board[i][j] = '#';
            }else{
                board[i][j] = ' ';
            }
        }
    }
    board[player_y][player_x] = 'R';
    board[enemy_y][enemy_x] = 'M';
}

void GameBoard::generate_inner_walls(){
    int seed = std::time(0);
    std::srand(seed);
    int wall_count(0);
    int rand_x, rand_y;
    while(wall_count < 2 * (width + height)){
        rand_x = std::rand() % (width - 2) + 1;
        rand_y = std::rand() % (height - 2) + 1;
        if(board[rand_y][rand_x] == ' ') board[rand_y][rand_x] = '#';
        ++wall_count;
    }
}

bool GameBoard::check_board(){
    std::set<std::pair<int, int>> visited;
    return path_check(&visited, std::pair<int, int>(player_x, player_y));
}

bool path_check(std::set<std::pair<int, int>>* visited, std::pair<int, int> current){
    if(visited->find(current) != visited->end()){
        return true;
    }
    return false;
}