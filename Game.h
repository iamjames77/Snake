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
  void Play(); // Game 실행 함수
  bool kbhit(); // 키보드 입력확인 함수
  void MakeMap(); //Map 생성
  void GameSuccess();//게임 성공시 윈도우 출력
  void GameFail();//게임 실패시 윈도우 출력
  void LevelUp(int lv);//map level에 따라 map 수정
  void printmap(); //Map 출력
  void SnakeLoc(); //Snake의 위치 정보 업데이트
  void SnakeMove(int* key);//Snake 이동함수
  void Gate();//Gate 생성 함수
  void GateNotOnTheWall(int* x, int *y,int **key,int data); //Gate 외벽이 아닌 내벽에 있을 시 실행되는 함수
  void Growth();//Snake 길이 증가
  void Poison();//Snake 길이 감소
  void scoreboard();//점수판 
};
