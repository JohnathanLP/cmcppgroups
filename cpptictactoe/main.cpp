#include <iostream>
#include "game.hpp"

int main()
{
  Game myGame;
  int turn = 0;
  bool gameOver = false;
  int rowIn;
  int colIn;
  bool turnOver = false;

  std::cout << "Welcome to the game!" << std::endl;

  //Loops until the game is over
  while(gameOver == false)
  {
    //Prints current board, announces whos turn it is
    myGame.printBoard();
    if(turn == 0)
    {
      std::cout << "It is Player One's Turn!" << std::endl;
    }
    else
    {
      std::cout << "It is Player Two's Turn!" << std::endl;
    }

    //Loops until turn is over
    while(turnOver == false)
    {
      std::cout << "Pick a Row: ";
      std::cin >> rowIn;
      std::cout << "Pick a Collumn: ";
      std::cin >> colIn;

      //makeMove returns false unless the move is legal
      turnOver = myGame.makeMove(turn, rowIn, colIn);
    }
    turnOver = false;

    //increments turn, then rounds it, so it alternates 0 and 1
    turn++;
    turn %= 2;
  }
}
