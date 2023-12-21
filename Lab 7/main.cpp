// Main
// ~~~~~~~~~~~~~
// NOTE
// I was making final changes in my code when switching around my cout functions
// when I got a popup saying "fix in ostream", mistakenly I pressed it. So now
// the code won't run and I tried copying and pasting into a new file and it wouldn't
// work there. So I think it is just a problem with my xcode system, or clientside,
// however I do not have time to redownload it as people on Online forums suggest.
// Sorry if the code does not run but the last time I ran it I had it close to working
// with two fully functional boards. Just didn't get the loop correctly finished.
// 
// ~~~~~~~~~~~~

#include "Battleship.hpp"

// Calling Functions
void PlayGame();

// Run Program
int main()
{
    PlayGame();
    
    BattleshipBoard board;
    
    board.Instructions();
    
    board.playGame();
    return 0;
}
