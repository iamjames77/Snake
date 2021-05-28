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
    g1.SnakeMove(key);
    if(g1.grow%5 == 0 && g1.item<3 && g1.item_g!=1)
    {
      g1.Growth();
      g1.grow = 0;
      g1.item++;
      g1.item_g++;
    }
    if(g1.poison%5 == 0 && g1.item<3 && g1.item_g!=0)
    {
      g1.Poison();
      g1.poison = 0;
      g1.item++;
    }
    g1.grow++;
    g1.poison++;
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
