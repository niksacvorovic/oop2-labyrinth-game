#include "GameBoard.hpp"
#include <cstdlib>
#include <chrono>
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
    int max_wall_count = 0.3 * width * height;
    int rand_x, rand_y;
    while(wall_count < max_wall_count){
        rand_x = std::rand() % (width - 2) + 1;
        rand_y = std::rand() % (height - 2) + 1;
        if(board[rand_y][rand_x] == ' ') board[rand_y][rand_x] = '#';
        ++wall_count;
    }
}

bool GameBoard::check_board(){
    std::set<std::pair<int, int>> visited;
    return path_check(&visited, std::pair<int, int>(player_y, player_x));
}

bool GameBoard::path_check(std::set<std::pair<int, int>>* visited, std::pair<int, int> current){
    if(visited->find(current) != visited->end()){
        return false;
    } else {
        visited->insert(current);
    }
    if(current.first == enemy_y && current.second == enemy_x){
        return true;
    } else if (board[current.first][current.second] == '#' || board[current.first][current.second] == 'U'){
        return false;
    } else {
        std::pair<int, int> left(current.first, current.second - 1);
        std::pair<int, int> down(current.first + 1, current.second);
        std::pair<int, int> right(current.first, current.second + 1);
        std::pair<int, int> up(current.first - 1, current.second);
        return path_check(visited, left) || path_check(visited, down) || path_check(visited, right) || path_check(visited, up);
    }
}

void GameBoard::set_items(){
    int items(0);
    int item_x, item_y;
    while(items < item_count){
        item_x = std::rand() % (width - 2) + 1;
        item_y = std::rand() % (height - 2) + 1;
        if(board[item_y][item_x] == ' '){
            board[item_y][item_x] = 'P';
            ++items;
        }
    }
}

void GameBoard::generate(){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    do{
        std::cout << '.';
        this->generate_outer_walls();
        this->generate_inner_walls();
    }while(!this->check_board());
    this->set_items();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Vreme za generisanje table (u mikrosekundama) " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << '\n';
}