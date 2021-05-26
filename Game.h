#include <iostream>
#include <vector>
#include <algorithm>
#include <ncurses.h>
#include <clocale>
using namespace std;

class Game{
  int snakesize;
  int **map;
  int row;
  int col;
  vector<pair<int, int>> v;
  vector<pair<int, int>>::iterator it;
public:
  Game(int r = 21, int c =21);
  void MakeMap();
  void printmap();
  void SnakeLoc();
  void SnakeUp();
  void SnakeDown();
  void SnakeLeft();
  void SnakeRight();
};