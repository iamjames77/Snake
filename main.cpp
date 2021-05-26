#include <iostream>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <locale.h>
#include "Game.h"
using namespace std;

int main()
{
  Game g1(21,21);
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  int key;
  g1.printmap();
  endwin();
}
