#include <iostream>
#include <vector>
#include <ncurses.h>
#include <algorithm>
#include <unistd.h>
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
  map[v.front().first][v.front().second] =3 ;
  for(int i=1; i<v.size(); i++)
  {
    map[v[i].first][v[i].second] = 4;
  }
}
void Game::SnakeMove(int key)
{
  int x,y;
  switch (key){
    case KEY_LEFT:
        x = v.front().first;
        y = v.front().second-1;
        break;
    case KEY_RIGHT:
        x = v.front().first;
        y = v.front().second+1;
        break;
    case KEY_UP:
        x = v.front().first-1;
        y = v.front().second;
        break;
    case KEY_DOWN:
        x = v.front().first+1;
        y = v.front().second;
        break;
    }
    if(map[x][y] == 0 || (x==v.back().first && y == v.back().second))
    {
      map[v.back().first][v.back().second] = 0;
      v.pop_back();
      v.insert(v.begin(),make_pair(x,y));
    }
    else if(map[x][y] == 5)
    {
      v.insert(v.begin(),make_pair(x,y));
      item--;
      item_g--;
    }
    else if(map[x][y] == 6)
    {
      map[v.back().first][v.back().second] = 0;
      v.pop_back();
      map[v.back().first][v.back().second] = 0;
      v.pop_back();
      v.insert(v.begin(),make_pair(x,y));
      item--;
    }
    printmap();
}

void Game::Growth()
{
  srand(time(NULL));
  int x = rand() % (row-2) + 1;
  int y = rand() % (col-2) + 1;
  while(map[x][y]!=0)
  {
    x = rand() % (row-2) + 1;
    y = rand() % (col-2) + 1;
  }
  map[x][y] =5;
}

void Game::Poison()
{
  srand(time(NULL));
  int x = rand() % (row-2) + 1;
  int y = rand() % (col-2) + 1;
  while(map[x][y]!=0)
  {
    x = rand() % (row-2) + 1;
    y = rand() % (col-2) + 1;
  }
  map[x][y] =6;
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
        mvprintw(i,2*j,"H ");
      }
      else if (map[i][j] == 4)
      {
        mvprintw(i,2*j,"B ");
      }
      else if (map[i][j] == 5)
      {
        mvprintw(i,2*j,"G ");
      }
      else if (map[i][j] == 6)
      {
        mvprintw(i,2*j,"P  ");
      }
    }
    printw("\n");
  }
  refresh();
}
