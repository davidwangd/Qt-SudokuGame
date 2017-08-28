#ifndef SOLVER_H
#define SOLVER_H
#include "const.h"
class Logic;
class Solver{
public:
    friend class Logic;
    Solver(Logic *logic): logic(logic){}
    int check();
    void* getBoard(){ return board; }
    void show();
private:
    int dfs(int x = 0, int y = 0, int flag = 0);
    Logic *logic;
    int board[10][10];
    int row[10][10];
    int col[10][10];
    int block[4][4][10];
    int num;
};


#endif // SOLVER_H
