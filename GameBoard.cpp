#include "GameBoard.hpp"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <set>

// Implementacija svih funkcionalnosti vezanih za generisanje table i proveru njene ispravnosti

GameBoard::~GameBoard(){
    for(int i = 0; i < height; ++i){
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Generisanje ulaza, izlaza i spoljašnjih zidova
void GameBoard::generate_outer_walls(int player_x, int player_y, int enemy_x, int enemy_y){
    int seed = std::time(0);
    std::srand(seed);
    for(int i = 0; i < width; ++i){
        if (i == player_x){
            matrix[0][i] = 'U';
        }else{
            matrix[0][i] = '#';
        }
        if (i == enemy_x){
            matrix[height - 1][i] = 'I';
        }else{
            matrix[height - 1][i] = '#';
        }
    }
    for(int i = 1; i < height - 1; ++i){
        for(int j = 0; j < width; ++j){
            if(j == 0 || j == width - 1){
                matrix[i][j] = '#';
            }else{
                matrix[i][j] = ' ';
            }
        }
    }
    matrix[player_y][player_x] = 'R';
    matrix[enemy_y][enemy_x] = 'M';
}

// Generisanje unutrašnjih zidova - vrši se nasumično
void GameBoard::generate_inner_walls(){
    int seed = std::time(0);
    std::srand(seed);
    int wall_count(0);
    // Heuristika za broj zidova
    int max_wall_count = 0.3 * width * height;
    int rand_x, rand_y;
    while(wall_count < max_wall_count){
        rand_x = std::rand() % (width - 2) + 1;
        rand_y = std::rand() % (height - 2) + 1;
        if(matrix[rand_y][rand_x] == ' ') matrix[rand_y][rand_x] = '#';
        ++wall_count;
    }
}

// Funkcija koja proverava da li je lavirint rešiv - po principu pretrage po dubini
bool GameBoard::check_board(int player_x, int player_y, int enemy_x, int enemy_y){
    std::set<std::pair<int, int>> visited;
    std::pair<int, int> starting(player_y, player_x);
    std::pair<int, int> final(enemy_y, enemy_x);
    return path_check(&visited, starting, final);
}

// Pomoćna funkcija za check_board koja se rekurzivno poziva
bool GameBoard::path_check(std::set<std::pair<int, int>>* visited, std::pair<int, int>& current, std::pair<int, int>& final){
    // Ukoliko find funkcija ne nađe element - vraća end iterator
    if(visited->find(current) != visited->end()){
        return false;
    } else {
        visited->insert(current);
    }
    if(current == final){
        return true;
    } else if (matrix[current.first][current.second] == '#' || matrix[current.first][current.second] == 'U'){
        return false;
    } else {
        std::pair<int, int> left(current.first, current.second - 1);
        std::pair<int, int> down(current.first + 1, current.second);
        std::pair<int, int> right(current.first, current.second + 1);
        std::pair<int, int> up(current.first - 1, current.second);
        return path_check(visited, left, final) || path_check(visited, down, final) || path_check(visited, right, final) || path_check(visited, up, final);
    }
}

// Funkcija koja nasumično raspoređuje predmete po tabli
void GameBoard::set_items(){
    int items(0);
    int item_x, item_y;
    // Ograničavamo broj predmeta na maksimalno 60% polja
    while(items < item_count && items < 0.6 * width * height){
        item_x = std::rand() % (width - 2) + 1;
        item_y = std::rand() % (height - 2) + 1;
        if(matrix[item_y][item_x] == ' '){
            matrix[item_y][item_x] = 'P';
            ++items;
        }
    }
}

// Obuhvata sve funkcije za generisanje table u jedan poziv
void GameBoard::generate(int player_x, int player_y, int enemy_x, int enemy_y){
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    do{
        generate_outer_walls(player_x, player_y, enemy_x, enemy_y);
        generate_inner_walls();
    }while(!check_board(player_x, player_y, enemy_x, enemy_y));
    set_items();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Vreme za generisanje table (u mikrosekundama) " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << '\n';
}

int GameBoard::get_width(){
    return width;
} 

int GameBoard::get_height() {
    return height;
}

std::ostream& operator<<(std::ostream& os, const GameBoard& g){
    for(int i = 0; i < g.height; ++i){
        for(int j = 0; j < g.width; ++j){
            os << g.matrix[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

char* GameBoard::operator[](int index){
    return matrix[index];
}