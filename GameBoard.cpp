#include "GameBoard.hpp"
#include <iostream>

GameBoard::~GameBoard(){
    for(int i = 0; i < height; ++i){
        delete[] board[i];
    }
    delete[] board;
}

std::ostream& operator<<(std::ostream& os, const GameBoard& g){
    for(int i = 0; i < g.height; ++i){
        for(int j = 0; j < g.width; ++j){
            os << g.board[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}