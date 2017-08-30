#include "solver.h"
#include "logic.h"
#include <algorithm>
#include "const.h"
#include "debug.h"
#include <QApplication>
using namespace std;

int Solver::check(){
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(block, 0, sizeof(block));

    for (int i = 0;i < SIZE;i++){
        for (int j = 0;j < SIZE;j++){
            if (logic -> used[i][j]){
                int f = logic -> ans[i][j];
                board[i][j] = f;
                if (row[i][f] || col[j][f] || block[i/3][j/3][f]) return 0;
                row[i][f] = 1;
                col[j][f] = 1;
                block[i/3][j/3][f] = 1;
            }else{
                board[i][j] = 0;
            }
        }
    }
    num = 0;
    int ret = dfs(0, 0);

    return ret;
}


int Solver::dfs(int x, int y, int flag){
    if (x == SIZE - 1 && y == SIZE) return flag;
    if (y == SIZE) return dfs(x+1, 0, flag);
    if (board[x][y]) return dfs(x, y+1, flag);
    for (int j = 1;j <= SIZE;j++){
        if (!row[x][j] && !col[y][j] && !block[x/3][y/3][j]){
            row[x][j] = 1;
            col[y][j] = 1;
            block[x/3][y/3][j] = 1;
            board[x][y] = j;
            if (dfs(x, y+1, flag | (j != logic -> ans[x][y]))) return 1;
            board[x][y] = 0;
            row[x][j] = 0;
            col[y][j] = 0;
            block[x/3][y/3][j] = 0;
        }
    }
    return 0;
}

void Solver::show(){

}
