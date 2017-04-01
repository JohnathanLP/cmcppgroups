#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"

//Size of the window
#define HIGH 600
#define WIDE 600

//Defines the positions of each row and collumn
#define POS1 28
#define POS2 228
#define POS3 428

int main()
{
  Game myGame;
  int mouseX, mouseY, moveX, moveY;
  int turn = 0;

  //Creates Window
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH), "TicTacToe");

  //Loads the texture for the board grid
  sf::Texture boardTexture;
  if(!boardTexture.loadFromFile("board.png"))
  {
    //Throws this error if texture load fails
    std::cout << "Error loading textures" << std::endl;
    return 0;
  }
  //Sprite for the board grid
  sf::Sprite boardSprite;
  boardSprite.setTexture(boardTexture);
  boardSprite.setPosition(12,12);

  //Loads the texture for the X and O
  sf::Texture xandoTexture;
  if(!xandoTexture.loadFromFile("xando.png"))
  {
    //Throws this error if the texture load fails
    std::cout << "Error loading textures" << std::endl;
    return 0;
  }
  //Sprite for the X
  sf::Sprite xSprite;
  xSprite.setTexture(xandoTexture);
  xSprite.setTextureRect(sf::IntRect(0,0,160,160));
  //Sprite for the O
  sf::Sprite oSprite;
  oSprite.setTexture(xandoTexture);
  oSprite.setTextureRect(sf::IntRect(0,160,160,160));

  //Loads the font for the victory message
  sf::Font font;
  if(!font.loadFromFile("raidercrusadershiftdown.ttf"))
  {
    //Throws this error if the font load fails
    std::cout << "Error loading font!" << std::endl;
    return 0;
  }
  //Text for the victory message
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(48);
  text.setColor(sf::Color::Black);
  text.setPosition(WIDE/2,HIGH/2);

  //Loops as long as window is open
  while(window.isOpen())
  {
    //Loops through all events that have occurred since last loop
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        //Closes the window if a close event is received
        window.close();
      }
      if(event.type == sf::Event::MouseButtonPressed)
      {
        //If mouse is clicked, checks if it was the left mouse button
        if(event.mouseButton.button == sf::Mouse::Left)
        {
          //Loads in the x and y position of the mouse button at the time of the click
          mouseX = event.mouseButton.x;
          mouseY = event.mouseButton.y;

          //figure out which collumn was clicked
          if(POS1 <= mouseX && mouseX <= POS1+160)
          {
            moveX = 0;
          }
          if(POS2 <= mouseX && mouseX <= POS2+160)
          {
            moveX = 1;
          }
          if(POS3 <= mouseX && mouseX <= POS3+160)
          {
            moveX = 2;
          }

          //figure out which row was clicked
          if(POS1 <= mouseY && mouseY <= POS1+160)
          {
            moveY = 0;
          }
          if(POS2 <= mouseY && mouseY <= POS2+160)
          {
            moveY = 1;
          }
          if(POS3 <= mouseY && mouseY <= POS3+160)
          {
            moveY = 2;
          }

          //If the move was legal, switch over the turn
          if(myGame.makeMove(turn, moveY, moveX) == true)
          {
            turn++;
            turn %= 2;
          }
          //Uncomment this line if you want it to print the board to the terminal (for debugging)
          //myGame.printBoard();
        }
      }
    }

    //clears the window
    window.clear(sf::Color::White);

    //redraws all the X's and O's - loops through all 9 spaces
    for(int i=0; i<3; i++)
    {
      for(int j=0; j<3; j++)
      {
        //reads character in space
        char space = myGame.getSpace(i,j);
        int xPos, yPos;
        //If the space isn't blank, sets xPos and yPos
        if(space != ' ')
        {
          if(i == 0)
          {
            xPos = POS1;
          }
          else if(i == 1)
          {
            xPos = POS2;
          }
          else if(i == 2)
          {
            xPos = POS3;
          }
          if(j == 0)
          {
            yPos = POS1;
          }
          else if(j == 1)
          {
            yPos = POS2;
          }
          else if(j == 2)
          {
            yPos = POS3;
          }
        }
        //If the space is an X, print an X there
        if(space == 'X')
        {
          xSprite.setPosition(yPos, xPos);
          window.draw(xSprite);
        }
        //If the space is an O, print an O there
        else if(space == 'O')
        {
          oSprite.setPosition(yPos, xPos);
          window.draw(oSprite);
        }
      }
    }

    //Check for victory, prints a message
    if(myGame.testForWin())
    {
      if(turn == 0)
      {
        text.setString("O Wins!");
      }
      else
      {
        text.setString("X Wins!");
      }
      window.draw(text);
    }

    //Draws the board, then updates the window
    window.draw(boardSprite);
    window.display();
  }
}
