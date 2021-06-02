//Game.h
#include <iostream>
#include <vector>
#include <algorithm>
#include <ncurses.h>
#include <clocale>
using namespace std;

class Game{
  int **map;
  int row;
  int col;
  int level;
  int item = 0;
  int item_g=0;
  int grow = 0;
  int poison = 0;
  int g_number = 0;
  int p_number = 0;
  int gate = 0;
  int g1_x = 0;
  int g1_y = 0;
  int g2_x = 0;
  int g2_y = 0;
  int gate_number = 0;
  vector<pair<int, int>> v;
  vector<pair<int, int>>::iterator it;
public:
  Game(int r = 21, int c =21, int level = 1);
  void Play();
  bool kbhit();
  void MakeMap(); //Map 생성
  void GameSuccess();
  void GameFail();
  void LevelUp(int lv);
  void printmap(); //Map 출력
  void SnakeLoc(); //Snake의 위치 정보 업데이트
  void SnakeMove(int* key);
  void Gate();
  void GateNotOnTheWall(int* x, int *y,int **key,int data);
  void Growth();
  void Poison();
  void scoreboard();
};
