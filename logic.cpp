#include "logic.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "debug.h"
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

void Logic::generateEasyGame(){
    generate(40);
}

void Logic::generateNormalGame(){
    generate(55);
}

void Logic::generateHardGame(){
    generate(60);
}

int Logic::generate(int steps){
    // TODO
    return 0;
}

int Logic::check(){
    // TODO
}

int Logic::simpleCheck(){
    // TODO
}

void Logic::process(const Operation &cur, int toShow){
    int x = cur.x;
    int y = cur.y;
    int now = cur.num;
#ifdef DEBUG
    printf("process(%d,%d,%d,%d)\n", x, y, cur.flag, cur.num);
#endif
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
            if (now == 0){
                notes[x][y].clear();
            }
        //    window -> grid[x][y] -> setText(QString::number(grid[x][y]));
        //    printf("grid[%d][%d] = %d\n", x, y, now);
        }else{
            grid[x][y] = 0;
            notes[x][y].clear();
        }
    }
    if (toShow){
        updateFrame();
    }
}

int Logic::pushNumber(int x){
    // TODO
#ifdef DEBUG
    fprintf(stdout, "pushNumber(%d)\n", x);
#endif
    if (pre_x != -1 && pre_y != -1){
        Operation cur(pre_x, pre_y, x, m_note);
        operations.push_back(cur);
        process(cur);
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
            if (grid[i][j]){
                window -> grid[i][j] -> setText(QString::number(grid[i][j]));
                if (grid[i][j] == num)
                    window -> grid[i][j] -> setStyleSheet(btnHighlightSecondStyle);
                else
                    window -> grid[i][j] -> setStyleSheet(btnNormalStyle);
            }else{
                window -> grid[i][j] -> setStyleSheet(btnNormalStyle);
                if (notes[i][j].size()){
                    buffer[0] = 0;
                    for (int k = 0;k < notes[i][j].size();k++){
                        if (!k) sprintf(buffer + strlen(buffer), ",");
                        sprintf(buffer + strlen(buffer), "%d", notes[i][j][k]);
                    }
                    window -> grid[i][j]->setText(buffer);
                }else{
                    window -> grid[i][j] -> setText("");
                }
            }
        }
    }
    if (pre_x != -1 && pre_y != -1)
        window -> grid[pre_x][pre_y] -> setStyleSheet(btnHighlightSyle);
}

// revoke the last operation
void Logic::revoke(){
    int last = operations.size();
    operations.erase(operations.begin() + (last - 1));
    for (auto t : operations){
        process(t, 0);
    }
    updateFrame();
}

int Logic::selfCheck(){
    // TODO
    // Totally TODO Matter.
    return 1;
}
