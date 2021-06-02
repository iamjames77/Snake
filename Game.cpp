#include <iostream>
#include <vector>
#include <ncurses.h>
#include <algorithm>
#include <unistd.h>
#include <clocale>
#include "Game.h"
using namespace std;

Game::Game(int r,int c,int lv){
  row = r;
  col = c;
  level = lv;
  map = new int*[row];
  for(int i=0;i<row;i++)
  {
    map[i] = new int[col];
  }
  snakesize = 3;
  MakeMap();
}

void Game::Play()
{
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  resize_term(row*2,col*3);
  int key = KEY_LEFT;
  int a;
  printmap();
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
    SnakeMove(&key);
    if(grow%10 == 0 && item<3 && item_g!=1)
    {
      Growth();
      grow = 0;
      item++;
      item_g++;
    }
    if(poison%10 == 0 && item<3 && item_g!=0)
    {
      Poison();
      poison = 0;
      item++;
    }
    if(gate % 40 == 0)
    {
      Gate();
    }
    gate++;
    grow++;
    poison++;
    if(v.size()<2)
    {
      GameFail();
    }
    if(v.size() >= 7 && g_number >= 5 && p_number >= 2 && gate_number >=2)
    {
      GameSuccess();
      break;
    }
    usleep(500000);
  }
}

bool Game::kbhit()
{
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
  v.clear();
  if (level == 1)
  {
    v.push_back(make_pair(row/2, col/2 - 1));
    v.push_back(make_pair(row/2, col/2));
    v.push_back(make_pair(row/2, col/2 + 1));
  }
  else if (level == 2)
  {
    v.push_back(make_pair(3*row/4, 3*col/4 - 1));
    v.push_back(make_pair(3*row/4, 3*col/4));
    v.push_back(make_pair(3*row/4, 3*col/4 + 1));
  }
  LevelUp(level);
}

void Game::LevelUp(int lv)
{
  if(lv == 2)
  {
    for(int i=4;i<row-4;i++)
    {
      map[col/2][i] = 1;
    }
    for(int i=4;i<col-4;i++)
    {
      map[i][row/2] = 1;
    }
    map[col/2][row/2] = 2;
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
void Game::SnakeMove(int* key)
{
  int x,y;
  switch (*key){
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
      g_number++;
    }
    else if(map[x][y] == 6)
    {
      map[v.back().first][v.back().second] = 0;
      v.pop_back();
      map[v.back().first][v.back().second] = 0;
      v.pop_back();
      v.insert(v.begin(),make_pair(x,y));
      item--;
      p_number++;
    }
    else if(map[x][y] == 7)
    {
      map[v.back().first][v.back().second] = 0;
      v.pop_back();
      if(g2_x == 0)
      {
        x = g2_x + 1;
        y = g2_y;
        *key = KEY_DOWN;
      }
      else if (g2_x == row-1)
      {
        x = g2_x - 1;
        y = g2_y;
        *key = KEY_UP;
      }
      else if (g2_y == 0)
      {
        x = g2_x;
        y = g2_y + 1;
        *key = KEY_RIGHT;
      }
      else if (g2_y == col-1)
      {
        x = g2_x;
        y = g2_y-1;
        *key = KEY_LEFT;
      }
      else
      {
        GateNotOnTheWall(&x,&y,&(key),7);
      }
      v.insert(v.begin(),make_pair(x,y));
      gate_number++;
    }
    else if(map[x][y] == 8)
    {
      map[v.back().first][v.back().second] = 0;
      v.pop_back();
      if(g1_x == 0)
      {
        x = g1_x + 1;
        y = g1_y;
        *key = KEY_DOWN;
      }
      else if (g1_x == row-1)
      {
        x = g1_x - 1;
        y = g1_y;
        *key = KEY_UP;
      }
      else if (g1_y == 0)
      {
        x = g1_x;
        y = g1_y + 1;
        *key = KEY_RIGHT;
      }
      else if (g1_y == col-1)
      {
        x = g1_x;
        y = g1_y-1;
        *key = KEY_LEFT;
      }
      else
      {
        GateNotOnTheWall(&x,&y,&(key),8);
      }
      v.insert(v.begin(),make_pair(x,y));
      gate_number++;
    }
    else
    {
      GameFail();
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

void Game::Gate()
{
  if (map[g1_x][g1_y] == 7 && map[g2_x][g2_y] == 8)
  {
    map[g1_x][g1_y] = 1;
    map[g2_x][g2_y] = 1;
  }
  srand(time(NULL));
  int x = rand() % row;
  int y = rand() % col;
  while(map[x][y]!=1)
  {
    x = rand() % row;
    y = rand() % col;
  }
  map[x][y] =7;
  g1_x = x;
  g1_y = y;
  while(map[x][y]!=1)
  {
    x = rand() % row;
    y = rand() % col;
  }
  map[x][y] = 8;
  g2_x = x;
  g2_y = y;
}

void Game::GateNotOnTheWall(int *x, int* y, int **key, int data)
{
  int X, Y;
  int i=0;
  if(data == 7)
  {
    X = g2_x;
    Y = g2_y;
  }
  else if (data == 8)
  {
    X = g1_x;
    Y = g1_y;
  }
  switch(**key)
  {
    case KEY_UP:
    {
      if(map[X-1][Y]!=1 && map[X-1][Y]!= 2)
      {
        *x = X-1;
        *y = Y;
        **key = KEY_UP;
      }
      else if(map[X][Y+1]!=1 && map[X][Y+1] !=2)
      {
        *x = X;
        *y = Y+1;
        **key = KEY_RIGHT;
      }
      else if(map[X][Y-1]!=1 && map[X][Y-1] !=2)
      {
        *x = X;
        *y = Y-1;
        **key = KEY_LEFT;
      }
      else if(map[X+1][Y] !=1 && map[X+1][Y] !=2)
      {
        *x = X+1;
        *y = Y;
        **key = KEY_DOWN;
      }
      break;
    }
    case KEY_DOWN:
    {
      if(map[X+1][Y] != 1 && map[X+1][Y] !=2)
      {
        *x = X+1;
        *y = Y;
        **key = KEY_DOWN;
      }
      else if(map[X][Y-1]!=1 && map[X][Y-1] !=2)
      {
        *x = X;
        *y = Y-1;
        **key = KEY_LEFT;
      }
      else if(map[X][Y+1]!=1 && map[X][Y+1] !=2)
      {
        *x = X;
        *y = Y+1;
        **key = KEY_RIGHT;
      }
      else if(map[X-1][Y]!=1 && map[X-1][Y]!= 2)
      {
        *x = X-1;
        *y = Y;
        **key = KEY_UP;
      }
      break;
    }
    case KEY_RIGHT:
    {
      if (map[X][Y+1]!=1 && map[X][Y+1] !=2)
      {
        *x = X;
        *y = Y+1;
        **key = KEY_RIGHT;
      }
      else if(map[X+1][Y] !=1 && map[X+1][Y] !=2)
      {
        *x = X+1;
        *y = Y;
        **key = KEY_DOWN;
      }
      else if(map[X-1][Y]!=1 && map[X-1][Y]!= 2)
      {
        *x = X-1;
        *y = Y;
        **key = KEY_UP;
      }
      else if(map[X][Y-1]!=1 && map[X][Y-1] !=2)
      {
        *x = X;
        *y = Y-1;
        **key = KEY_LEFT;
      }
      break;
    }
    case KEY_LEFT:
    {
      if(map[X][Y-1]!=1 && map[X][Y-1] !=2)
      {
        *x = X;
        *y = Y-1;
        **key = KEY_LEFT;
      }
      else if(map[X-1][Y]!=1 && map[X-1][Y]!= 2)
      {
        *x = X-1;
        *y = Y;
        **key = KEY_UP;
      }
      else if(map[X+1][Y] !=1 && map[X+1][Y] !=2)
      {
        *x = X+1;
        *y = Y;
        **key = KEY_DOWN;
      }
      else if (map[X][Y+1]!=1 && map[X][Y+1] !=2)
      {
        *x = X;
        *y = Y+1;
        **key = KEY_RIGHT;
      }
      break;
    }
  }
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
      else if (map[i][j] == 7 || map[i][j] == 8)
      {
        mvprintw(i,2*j,"\u25A6 ");
      }
    }
    scoreboard();
    printw("\n");
  }
  refresh();
}

void Game::scoreboard()
{
  mvprintw(1,2*col+2,"Score Board");
  mvprintw(2,2*col+2,"B: %d / 7",v.size());
  mvprintw(3,2*col+2,"+: %d / 5",g_number);
  mvprintw(4,2*col+2,"-: %d / 2",p_number);
  mvprintw(5,2*col+2,"G: %d / 2",gate_number);
  mvprintw(row/2+1,2*col+2,"Misson Board");
  if(v.size() >= 7)
  {
    mvprintw(row/2+2,2*col+2,"B: 7(\u2713)");
  }
  else
  {
    mvprintw(row/2+2,2*col+2,"B: 7(\u2716)");
  }
  if(g_number >= 5)
  {
    mvprintw(row/2+3,2*col+2,"+: 5(\u2713)");
  }
  else
  {
    mvprintw(row/2+3,2*col+2,"+: 5(\u2716)");
  }
  if(p_number >= 2)
  {
    mvprintw(row/2+4,2*col+2,"-: 2(\u2713)");
  }
  else
  {
    mvprintw(row/2+4,2*col+2,"-: 2(\u2716)");
  }
  if(gate_number >= 2)
  {
    mvprintw(row/2+5,2*col+2,"G: 2(\u2713)");
  }
  else
  {
    mvprintw(row/2+5,2*col+2,"G: 2(\u2716)");
  }
  for(int i = col*2; i < 3 * col;i+=2)
  {
    mvprintw(0,i,"\u25A0");
    mvprintw(row/2,i,"\u25A0");
    mvprintw(row-1, i, "\u25A0");
  }
  for(int i = 0;i<row;i++)
  {
    mvprintw(i,col*2,"\u25A0");
    mvprintw(i,3*col-1,"\u25A0");
  }
}

void Game::GameFail()
{
  WINDOW* win1;
  win1 = newwin(row-2,col*2-4,1,2);
  start_color();
  mvwprintw(win1, row/2-1, col-14, "click any key to continue");
  wborder(win1, '*','*','*','*','*','*','*','*');
  wrefresh(win1);
  getch();
  item = 0;
  item_g=0;
  grow = 0;
  poison = 0;
  g_number = 0;
  p_number = 0;
  gate = 0;
  g1_x = 0;
  g1_y = 0;
  g2_x = 0;
  g2_y = 0;
  gate_number = 0;
  MakeMap();
  Play();
  delwin(win1);
}

void Game::GameSuccess()
{
  WINDOW* win1;
  win1 = newwin(row-2,col*3-4,1,2);
  start_color();
  mvwprintw(win1, row/2-1, col-14, "click any key to play next stage");
  wborder(win1, '*','*','*','*','*','*','*','*');
  wrefresh(win1);
  getch();
  delwin(win1);
}
