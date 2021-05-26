#include <iostream>
#include <vector>
#include <ncurses.h>
#include <algorithm>
#include <clocale>
#include "Game.h"
using namespace std;

Game::Game(int r,int c){
  row = r;
  col = c;
  map = new int*[row];
  for(int i=0;i<row;i++)
  {
    map[i] = new int[col];
  }
  snakesize = 3;
  v.push_back(make_pair(row/2, col/2 - 1));
  v.push_back(make_pair(row/2, col/2));
  v.push_back(make_pair(row/2, col/2 + 1));
  MakeMap();
}

void Game::MakeMap(){
  for(int i=0; i<col;i++)
  {
    if(i == 0 || i == col-1)
    {
      map[0][i] = 2;
      map[row-1][i] = 2;
    }
    else
    {
      map[0][i] = 1;
      map[row-1][i] =1;
    }
  }
  for(int i=1;i<row-1;i++)
  {
    for(int j=0;j<col;j++)
    {
      if(j==0||j==col-1)
      {
        map[i][j] = 1;
      }
      else
      {
        map[i][j] = 0;
      }
    }
  }
}

void Game::SnakeLoc()
{
  map[v[0].first][v[0].second] =3 ;
  for(int i=1; i<v.size(); i++)
  {
    map[v[i].first][v[i].second] = 4;
  }
}

void Game::SnakeUp()
{
  it = find(v.begin(), v.end(), make_pair(v[0].first-1,v[0].second));
  if(it == v.end())
  {
    v.insert(v.begin(),make_pair(v[0].first-1,v[0].second));
    v.pop_back();
  }
  MakeMap();
  printmap();
}

void Game::printmap(){
  SnakeLoc();
  for(int i=0;i<row;i++)
  {
    for(int j=0;j<col;j++)
    {
      if(map[i][j] == 2)
      {
        mvprintw(i,2*j,"\u25A3 ");
      }
      else if (map[i][j] == 1)
      {
        mvprintw(i,2*j,"\u25A0 ");
      }
      else if (map[i][j] == 0)
      {
        mvprintw(i,2*j,"\u25A1 ");
      }
      else if (map[i][j] == 3)
      {
        mvprintw(i,2*j,"A ");
      }
      else if (map[i][j] == 4)
      {
        mvprintw(i,2*j,"B ");
      }
    }
    printw("\n");
  }
  getch();
  refresh();
}
