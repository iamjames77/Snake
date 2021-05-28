//Game.h
#include <iostream>
#include <vector>
#include <algorithm>
#include <ncurses.h>
#include <clocale>
using namespace std;

class Game{
  int snakesize;
  int **map;
  vector<pair<int, int>> v;
  vector<pair<int, int>>::iterator it;
public:
  int row;
  int col;
  int item = 0;
  int item_g=0;
  int item_p=0;
  int grow = 0;
  int poison = 0;
  Game(int r = 21, int c =21);
  void MakeMap(); //Map 생성
  void printmap(); //Map 출력
  void SnakeLoc(); //Snake의 위치 정보 업데이트
  void SnakeMove(int key);
  void Growth();
  void Poison();
};
