#include <iostream>
#include <ncurses.h>
#include <vector>
#include <algorithm>
#include <locale.h>
#include <unistd.h>
#include "Game.h"
using namespace std;

bool kbhit();

int main()
{
  Game g1(21,21);
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  int key = KEY_LEFT;
  int a;
  int i = 21;
  g1.printmap();
  while(1)
  {
    if(kbhit())
    {
      if((a=getch())!=key){key =a;}
      else
      {
        continue; //contune를 안 쓰면 map이 출력이 됨.
      }
    }
    switch (key){
      case KEY_LEFT:
          g1.SnakeLeft();
          break;
      case KEY_RIGHT:
          g1.SnakeRight();
          break;
      case KEY_UP:
          g1.SnakeUp();
          break;
      case KEY_DOWN:
          g1.SnakeDown();
          break;
      }
    usleep(500000);
  }
  endwin();
}

bool kbhit(){
  int ch;
  bool ret;

  nodelay(stdscr, TRUE);

  ch = getch();
  if(ch==ERR){
    ret = false;
  }
  else{
    ret = true;
    ungetch(ch);
  }

  nodelay(stdscr,FALSE);
  return ret;
}
