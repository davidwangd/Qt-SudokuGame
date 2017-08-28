#ifndef LOGIC_H
#define LOGIC_H
#include "debug.h"
#include <QObject>
#include <vector>
#include "const.h"

class MainWindow;

struct Operation{
    int x, y, num, flag;
    Operation(){}
    Operation(int x, int y, int num, int flag): x(x), y(y), num(num), flag(flag){
    }
};

class Logic : public QObject{
    Q_OBJECT
    friend class MainWindow;
public:
    Logic(MainWindow *window, QObject *parent = 0): window(window), QObject(parent){
        memset(used, 0, sizeof(used));
        memset(ans, 0, sizeof(ans));
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(block, 0, sizeof(block));
        memset(grid, 0, sizeof(grid));
        pre_x = pre_y = -1;
        m_note = 0;
    }
public slots:
    void generateEasyGame();
    void generateNormalGame();
    void generateHardGame();
    void noteMode();
    void revoke();
    int check();
    int simpleCheck();
    void clear();
private:
    void process(const Operation &x, int toShow = 1);
    int pushNumber(int);
    void updateFrame();
    int pushPos(int x, int y);
    std::vector<int> notes[10][10];   // the notes
    int grid[10][10];           // to solve the current state
    int used[10][10];           // whether its for the user to put
    int ans[10][10];
    int row[10][10];
    int col[10][10];
    int block[4][4][10];
    int generate(int step = 0); // to generate a random sudoku with step empitys;
    int selfCheck(); // only one solution;
    int m_note;         // whether cuurently its note mode;
    MainWindow *window;
    int pre_x, pre_y;
    std::vector<Operation> operations;
};

#endif // LOGIC_H
