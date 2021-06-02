#include <iostream>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <locale.h>
#include <unistd.h>
#include "Game.h"
using namespace std;


int main()
{
  Game g1(21,21,1);
  g1.Play();
  Game g2(21,21,2);
  g2.Play();
  endwin();
}
