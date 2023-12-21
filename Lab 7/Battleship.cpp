// Cpp File
#include "Battleship.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include <chrono> // Wanted to simulate as if loading the game took time
#include <limits>
#include <ctime>
using namespace std;

// Play Game Intro
void PlayGame()
{
    int choice;
    
    while (true)
    {
        cout << setw(75) <<  "Welcome to Battleship!\n" << "\n1) New Game" << "\n2) Close Program" << "\n" << "> ";
        cin >> choice;
        if (choice==1)
        {
            cout << "Creating New Game...\n";
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Game Created! Let's start playing!\n\n";
            break;
        }
        else if (choice==2)
        {
            exit(0);
        } else
        {
            cout << "Error\n";
        }
                
    }
}

// Battleship Instructions
void BattleshipBoard::Instructions()
{
    int choice;
        cout << "Instructions:\n";
        cout << "1. The game is played on a 10x10 grid.\n";
        cout << "2. Your goal is to sink the enemy battleship by guessing its location.\n";
        cout << "3. You will place your battleship on the grid before the game starts.\n";
        cout << "Make sure to type exactly what is prompted and check your Caplock."
        cout << "4. To play, enter the row and column coordinates for your guess.\n";
        cout << "5. '~' represents water, '#' represents your ship, 'M' represents a miss, and 'H' represents a hit.\n";
        cout << "6. The game ends when you sink the enemy battleship or all of your battleships are sunk.\n";
        cout << "7. Have fun and good luck!\n";
        cout << "Would you like to continue? Type a number to start \n" << "< ";
        cin >> choice;
}

// Battleship Board
BattleshipBoard::BattleshipBoard()
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            playerBoard[i][j] = '~';
            aiBoard[i][j] = '~';
        }
    }
    
    // Seed for random number generation
        srand(time(0));
}

// Player Board
void BattleshipBoard::displayPlayerBoard() const
{
    cout << "   A B C D E F G H I J\n"; // Column labels
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << setw(2) << i << " "; // Row label
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            cout << playerBoard[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

// AI Board
void BattleshipBoard::displayAIBoard() const
{
    cout << "   A B C D E F G H I J\n"; // Column labels
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        cout << setw(2) << i << " "; // Row label
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            cout << aiBoard[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

// Placing Ship
void BattleshipBoard::placeBattleship(int row, int col, char shipSymbol, int shipSize, bool isPlayer)
{
     // Check if there is enough space on the board to place the battleship
       if (col + shipSize > BOARD_SIZE)
       {
           cout << "Not enough space to place the battleship.\n";
           return;
       }

       // Place the battleship on the board
       for (int i = col; i < col + shipSize; ++i)
       {
           playerBoard[row][i] = shipSymbol;
       }
}

// If Space is Occupied
bool BattleshipBoard::isSpaceOccupied(int row, int col, int shipSize, bool isPlayer)
{
    const char (*board)[BOARD_SIZE];
    if (isPlayer)
    {
        board = playerBoard;
    } else {
        board = aiBoard;
    }

    // Check if the space is occupied by another ship
    for (int i = col; i < col + shipSize; ++i)
    {
        if (i >= 0 && i < BOARD_SIZE && board[row][i] != 'O')
        {
            return true;
        }
    }

    return false;
}

// Check if the Move is Valid
bool BattleshipBoard::isValidMove(int row, int col, int shipSize, bool isPlayer)
{
    const char (*board)[BOARD_SIZE];
    // Check if the move is within the board boundaries
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || col + shipSize > BOARD_SIZE)
    {
        cout << "Invalid move. Out of bounds.\n";
        return false;
    }
    if (isPlayer)
    {
        board = playerBoard;
    }
    else
    {
        board = aiBoard;
    }

    // Check if the space is occupied by another ship
    for (int i = col; i < col + shipSize; ++i)
    {
        if (board[row][i] != '#')
        {
            cout << "Invalid move. Space occupied by another ship.\n";
            return false;
        }
    }

    // If none of the above conditions are met, it's a valid move
    return true;
}

// AI Attack Function
void BattleshipBoard::aiAttack()
{
    int aiRow, aiCol;

    // Keep track of attacked coordinates
    vector<pair<int, int>> attackedCoordinates;
    
    // Generate random coordinates for the AI's attack
    do {
        aiRow = rand() % BOARD_SIZE;
        aiCol = rand() % BOARD_SIZE;

    } while (isCoordinateAttacked(aiRow, aiCol, attackedCoordinates) || playerBoard[aiRow][aiCol] != '~');

    // Mark the current coordinates as attacked
    attackedCoordinates.push_back(make_pair(aiRow, aiCol));

    // Simulate the AI's attack on the player's board
    cout << "AI attacks at (" << aiRow << ", " << aiCol << "). ";
    if (playerBoard[aiRow][aiCol] != '~')
    {
        cout << "Hit!\n";
        playerBoard[aiRow][aiCol] = 'X';  // Mark as hit
    }
    else
    {
        cout << "Miss.\n";
        playerBoard[aiRow][aiCol] = 'M';  // Mark as miss
    }

    // Display the updated state of the player's board after the AI's attack
    displayPlayerBoard();
}

// Player Attack Function
void BattleshipBoard::playerAttack()
{
    int playerRow, playerCol;

    do {
        cout << "Enter the row and column to attack (0-9): ";
        cin >> playerRow >> playerCol;

    } while (!isValidMove(playerRow, playerCol, 1, false) || isCoordinateAttacked(playerRow, playerCol, attackedCoordinates));

    // Mark the current coordinates as attacked
    attackedCoordinates.push_back(make_pair(playerRow, playerCol));

    // Simulate the player's attack on the AI's board
    cout << "Player attacks at (" << playerRow << ", " << playerCol << "). ";
    if (aiBoard[playerRow][playerCol] != '~')
    {
        cout << "Hit!\n";
        aiBoard[playerRow][playerCol] = 'X';  // Mark as hit
    }
    else
    {
        cout << "Miss.\n";
        aiBoard[playerRow][playerCol] = 'M';  // Mark as miss
    }

    // Display the updated state of the AI's board after the player's attack
    displayAIBoard();
}



bool BattleshipBoard::isCoordinateAttacked(int row, int col, const vector<pair<int, int>>& attackedCoordinates)
const
{
    // Check if the coordinate has been attacked before
    for (const auto& coord : attackedCoordinates)
    {
        if (coord.first == row && coord.second == col)
        {
            cout << "Invalid move. Coordinate already attacked.\n";
            return true;
        }
    }

    return false;
}

// Check if All Ships are Sunk
bool BattleshipBoard::areAllShipsSunk(const char board[BOARD_SIZE][BOARD_SIZE]) const
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == '#' || board[i][j] == '#' || board[i][j] == '#' ||
                board[i][j] == '#' || board[i][j] == '#')
            {
                return false;
            }
        }
    }
    return true;
}


void BattleshipBoard::playGame()
{
    // Player's turn
    cout << "Player's Turn:\n";
    char playAgain;
    do {
        // Get user input for battleship type and placement
        string shipType;
        
        cout << "Enter the type of battleship (Carrier, Battleship, Cruiser, Submarine, Destroyer): ";
        cin >> shipType;
        
        char shipSymbol;
        int shipSize;
        char orientation;
        int row, col;
        
        if (shipType == "Carrier" || shipType == "carrier")
        {
            shipSymbol = '#';
            shipSize = 5;
        }
        else if (shipType == "Battleship" || shipType == "battleship")
        {
            shipSymbol = '#';
            shipSize = 4;
        }
        else if (shipType == "Cruiser" || shipType == "cruiser")
        {
            shipSymbol = '#';
            shipSize = 3;
        }
        else if (shipType == "Submarine" || shipType == "submarine")
        {
            shipSymbol = '#';
            shipSize = 3;
        }
        else if (shipType == "Destroyer" ||shipType == "destroyer" )
        {
            shipSymbol = '#';
            shipSize = 2;
        }
        else
        {
            cout << "Invalid battleship type. Please enter a valid type.\n";
            continue;
        }
        
        // Get user input for orientation (H for horizontal, V for vertical)
            cout << "Enter the orientation (H for horizontal, V for vertical): ";
            cin >> orientation;

        // Adjust placement based on orientation
    if (orientation == 'H' || orientation == 'h')
    {
        cout << "Enter the column and row to place the battleship (A - J | 0 - 9) for " << shipType << ": ";
        cin >> col >> row;
    }
    else if (orientation == 'V' || orientation == 'v')
    {
            cout << "Enter the column and row to place the battleship (A - J | 0 - 9) for " << shipType << ": ";
            cin >> col >> row;
    }
    else
    {
            cout << "Invalid orientation. Please enter 'H' or 'V'.\n";
            continue;
    }
        

        
        // Check if the input coordinates are within the valid range
if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
{
    // Place the battleship on the board
    placeBattleship(col, row, shipSymbol, shipSize, true);
            
    // Display the updated state of the board
    cout << "Updated Board:\n";
    displayPlayerBoard();
}
else
{
    cout << "Invalid coordinates. Please enter coordinates within the range (0-9)." << endl;
}
        
        // Ask the player if they want to place another battleship
        cout << "Do you want to place another battleship? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    // AI's turn
        cout << "AI's Turn:\n";
        aiAttack();
        displayPlayerBoard(); // Display the player's board after AI's attack

        // Player's and AI's turns until all ships are sunk
        while (!areAllShipsSunk(playerBoard) && !areAllShipsSunk(aiBoard))
        {
            // Player's turn
            cout << "Player's Turn:\n";
            playerAttack();
            displayAIBoard(); // Display the AI's board after player's attack

            // Check if all AI ships are sunk
            if (areAllShipsSunk(aiBoard)) {
                cout << "Congratulations! You've sunk all AI ships. You win!\n";
                return;
            }

            // AI's turn
            cout << "AI's Turn:\n";
            aiAttack();
            displayPlayerBoard(); // Display the player's board after AI's attack

            // Check if all player ships are sunk
            if (areAllShipsSunk(playerBoard))
            {
                cout << "AI has sunk all your ships. You lose!\n";
                return;
            }
        }

        cout << "The game has ended.\n";
}



