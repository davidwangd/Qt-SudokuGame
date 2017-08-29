#include "logic.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debug.h"
#include "solver.h"
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#ifdef DEBUG_GEN
    #define DEBUG_GEN_FIND \
        printf("!!\n");    \
        qApp -> quit();
#else
    #define DEBUG_GEN_FIND
#endif

using namespace std;

void Logic::generateEasyGame(){
    generate(35);
}

void Logic::generateNormalGame(){
    generate(50);
}

void Logic::generateHardGame(){
    generate(65);
}

int Logic::generate(int steps){
    memset(used, 0, sizeof(used));
    Solver solver(this);

    solver.check();
    for (int i = 0;i < SIZE;i++)
        for (int j = 0;j < SIZE;j++)
            ans[i][j] = solver.board[i][j];
    for (int i = 0;i < SIZE * SIZE;i++){
        int x = rand() & 1;
        int f = rand() % 3;
        int t1 = f * 3 + rand() % 3, t2 = f * 3 + rand() % 3;
        if (t1 == t2) continue;
        for (int j = 0;j < SIZE;j++){
            if (x) swap(ans[t1][j], ans[t2][j]);
            else swap(ans[j][t1], ans[j][t2]);
        }
    }

    static int order[100];
    for (int i = 0;i < 81;i++) order[i] = i;
    random_shuffle(order, order + SIZE * SIZE);
    int cnt = 0;
    for (int i = 0;i < SIZE;i++)
        for (int j = 0;j < SIZE;j++)
            used[i][j] = 1;
    for (int i = 0;i < SIZE * SIZE;i++){
        int x = order[i] / SIZE, y = order[i] % SIZE;
        used[x][y] = 0;

        if (solver.check()){
            used[x][y] = 1;
        }else{
            cnt++;
            if (cnt == steps) break;
        }
    }

    for (int i = 0;i < SIZE;i++)
        for (int j = 0;j < SIZE;j++){
            if (used[i][j]){
                grid[i][j] = ans[i][j];
                window -> grid[i][j] -> setFont(numberQustionFont);
            }else{
                grid[i][j] = 0;
            }
        }
    for (int i = 0;i < SIZE;i++)
        for (int j = 0;j < SIZE;j++)
            printf("%d%c", grid[i][j], j==SIZE-1?'\n':' ');
    updateFrame();
    return 0;
}

int Logic::check(){
    updateFrame();
    for (int i = 0;i < SIZE;i++)
        for (int j = 0;j < SIZE;j++){
            if (grid[i][j] != 0 && ans[i][j] != grid[i][j]){
                window -> grid[i][j] -> setStyleSheet(btnWrongStyle);
            }
        }
}

int Logic::simpleCheck(){
    updateFrame();
    static int row[10][10], col[10][10], block[4][4][10];
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(block, 0, sizeof(block));

    for (int i = 0;i < SIZE;i++)
        for (int j = 0;j < SIZE;j++){
            int &c = grid[i][j];
            if (c && (row[i][c] || col[j][c] || block[i/3][j/3][c])){
                window -> grid[i][j] -> setStyleSheet(btnWrongStyle);
            }
            row[i][c] = col[j][c] = block[i/3][j/3][c] = 1;
        }
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(block, 0, sizeof(block));

    for (int i = SIZE - 1;i >= 0;i--)
        for (int j = SIZE - 1;j >= 0;j--){
            int &c = grid[i][j];
            if (c && (row[i][c] || col[j][c] || block[i/3][j/3][c])){
                window -> grid[i][j] -> setStyleSheet(btnWrongStyle);
            }
            row[i][c] = col[j][c] = block[i/3][j/3][c] = 1;
        }
}

void Logic::process(const Operation &cur, int toShow){
    int x = cur.x;
    int y = cur.y;
    int now = cur.num;
#ifdef DEBUG
    printf("process(%d,%d,%d,%d)\n", x, y, cur.flag, cur.num);
#endif
    if (used[x][y]) return;
    if (cur.flag){
        grid[x][y] = 0;
        int flag = 0;
        for (int i = 0;i < notes[x][y].size();i++){
            if (notes[x][y][i] == now){
                flag = 1;
                notes[x][y].erase(notes[x][y].begin() + i);
                break;
            }
        }
        if (!flag){
            notes[x][y].push_back(now);
            sort(notes[x][y].begin(), notes[x][y].end());
        }
    }else{
        if (grid[x][y] != now){
            grid[x][y] = now;
            notes[x][y].clear();
            clearNotes(x, y);
        }
    }
    if (toShow){
        updateFrame();
    }
}

void Logic::clearNotes(int x, int y){
    int &now = grid[x][y];
    for (int i = 0;i < SIZE;i++){
        for (auto it = notes[x][i].begin(); it != notes[x][i].end();it++){
            if (*it == now){
                notes[x][i].erase(it);
                break;
            }
        }
        for (auto it = notes[i][y].begin(); it != notes[i][y].end();it++){
            if (*it == now){
                notes[i][y].erase(it);
                break;
            }
        }
    }
    for (int i = (x/3)*3; i < (x/3+1)*3;i++){
        for (int j = (y/3)*3; j < (y/3+1)*3;j++){
            for (auto it = notes[i][j].begin(); it != notes[i][j].end(); it++){
                if (*it == now){
                    notes[i][j].erase(it);
                    break;
                }
            }
        }
    }
}

int Logic::pushNumber(int x){
    for (int i = 1;i <= 9;i++){
        window -> number[i] -> setStyleSheet(i == x?btnPushedStyle:btnNormalStyle);
    }
    // TODO
#ifdef DEBUG
    fprintf(stdout, "pushNumber(%d)\n", x);
#endif
    if (pre_x != -1 && pre_y != -1 && !used[pre_x][pre_y] && grid[pre_x][pre_y] != x){
        Operation cur(pre_x, pre_y, x, m_note);
        operations.push_back(cur);
        process(cur);
        if (!m_note)
            pre_x = pre_y = -1;
    }
    else{
        for (int i = 0;i < 9;i++)
            for (int j = 0;j < 9;j++){
                window -> grid[i][j] -> setStyleSheet(grid[i][j] == x ? btnHighlightSecondStyle: btnNormalStyle);
            }
    }
}

int Logic::pushPos(int x, int y){
    // TODO
#ifdef DEBUG
    fprintf(stdout, "pushPos(%d, %d)\n", x, y);
#endif
    pre_x = x;
    pre_y = y;
    for (int i = 1;i <= SIZE;i++){
        window -> number[i] -> setStyleSheet(btnNormalStyle);
    }
    if (grid[x][y]) window -> number[grid[x][y]] -> setStyleSheet(btnPushedStyle);
    else{
        for (int i : notes[x][y]){
            window -> number[i] -> setStyleSheet(btnPushedStyle);
        }
    }
    updateFrame();
}

void Logic::clear(){
    if (pre_x == -1 || pre_y == -1) return;

    operations.push_back(Operation(pre_x, pre_y, 0, 0));
    process(Operation(pre_x, pre_y, 0, 0));
}

// TO set into note mode of the game
void Logic::noteMode(){
    // TODO
    m_note ^= 1;
    if (m_note){
        this -> window -> ui -> btnNoteMode -> setStyleSheet(btnPushedStyle);
    }else{
        this -> window -> ui -> btnNoteMode -> setStyleSheet(btnNormalStyle);
    }
}

void Logic::updateFrame(){
    static char buffer[100];
    memset(buffer, 0, sizeof(buffer));
#ifdef DEBUG
    QLabel A("updateFrame");
    A.show();
#endif
    int num;
    if (pre_x != -1 && pre_y != -1){
        num = grid[pre_x][pre_y];
    }else{
        num = -1;
    }
    for (int i = 0;i < 9;i++){
        for (int j = 0;j < 9;j++){
            QString sheet = QString();
            if (i == pre_x || j == pre_y){
                sheet = btnHighlightThirdSytle;
            }
            if (grid[i][j]){
                if (!used[i][j]) window -> grid[i][j] -> setFont(numberNormalFont);
                window -> grid[i][j] -> setText(QString::number(grid[i][j]));
                if (grid[i][j] == num)
                    sheet = sheet + btnHighlightSecondStyle;
            }else{
                if (notes[i][j].size()){
                    window -> grid[i][j] -> setFont(numberNoteFont);
                    buffer[0] = 0;
                    for (int k = 0;k < notes[i][j].size();k++){
                        if (k) sprintf(buffer + strlen(buffer), k%3?",":"\n");
                        sprintf(buffer + strlen(buffer), "%d", notes[i][j][k]);
                    }
                    window -> grid[i][j]->setText(buffer);
                }else{
                    window -> grid[i][j] -> setText("");
                }
            }
            window -> grid[i][j] -> setStyleSheet(sheet);
        }
    }
    for (int i = 1;i <= SIZE;i++)
        window -> number[i] -> setStyleSheet(btnNormalStyle);
    if (pre_x != -1 && pre_y != -1){
        window -> grid[pre_x][pre_y] -> setStyleSheet(btnHighlightSyle);
        if (grid[pre_x][pre_y]) window -> number[grid[pre_x][pre_y]] -> setStyleSheet(btnPushedStyle);
        else{
            for (int i : notes[pre_x][pre_y]){
                window -> number[i] -> setStyleSheet(btnPushedStyle);
            }
        }
    }
}

// revoke the last operation
void Logic::revoke(){
    int last = operations.size();
    if (last == 0) return;
    operations.erase(operations.begin() + (last - 1));
    for (int i = 0;i < 9;i++)
        for (int j = 0;j < 9;j++){
            if (!used[i][j]){
                notes[i][j].clear();
                grid[i][j] = used[i][j]?ans[i][j]:0;
            }
        }
    for (auto t : operations){
        process(t, 0);
    }
    updateFrame();
}

void Logic::hint(){
    if (pre_x != -1 && pre_y != -1){
        used[pre_x][pre_y] = 1;
        grid[pre_x][pre_y] = ans[pre_x][pre_y];
        window -> grid[pre_x][pre_y] -> setFont(numberQustionFont);
        clearNotes(pre_x, pre_y);
        updateFrame();
    }
}

int Logic::selfCheck(){
    // TODO
    // Totally TODO Matter.
    return 1;
}

void Logic::pause(){

}

void Logic::newSolver(){

}

void Logic::solve(){

}

void Logic::recover(){

}
