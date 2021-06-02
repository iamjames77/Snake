#include <iostream>
#include <ncurses.h>
#include "Game.h"
using namespace std;


int main()
{
  Game g1(21,21,1);
  g1.Play();
  Game g2(21,21,2);
  g2.Play();
  Game g3(21,21,3);
  g3.Play();
  Game g4(21,21,4);
  g4.Play();
  endwin();
}
