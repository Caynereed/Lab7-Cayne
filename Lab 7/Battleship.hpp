//  Battleship.hpp
//  Lab 7
//  Created by Cayne Reed on 12/4/23.

#ifndef Battleship_hpp
#define Battleship_hpp

#include <iostream>
using namespace std;

const int BOARD_SIZE = 10;

class BattleshipBoard
{
private:
    char playerBoard[10][10];
    char aiBoard[BOARD_SIZE][BOARD_SIZE];
    vector<pair<int, int>> attackedCoordinates;
public:
    BattleshipBoard();

    void displayPlayerBoard() const;
    
    void displayAIBoard() const;
    
    void placeBattleship(int row, int col, char shipSymbol, int shipSize, bool isPlayer);
    
    bool isSpaceOccupied(int row, int col, int shipSize, bool isPlayer);
    
    bool isValidMove(int row, int col, int shipSize, bool isPlayer);
    
    bool isCoordinateAttacked(int row, int col, const vector<pair<int, int>>& attackedCoordinates) const;
    
    void playGame();
    
    void aiAttack();
    
    void playerAttack();
    
    void Instructions();
    
    bool areAllShipsSunk(const char board[BOARD_SIZE][BOARD_SIZE]) const;

};

#endif /* Battleship_hpp */
