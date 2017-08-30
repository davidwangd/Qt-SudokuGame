#ifndef LOGIC_H
#define LOGIC_H
#include "debug.h"
#include <QObject>
#include <vector>
#include <QTimer>
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
    friend class Solver;
public:
    Logic(MainWindow *window, QObject *parent = 0): window(window), QObject(parent){
        memset(used, 0, sizeof(used));
        memset(ans, 0, sizeof(ans));
        memset(grid, 0, sizeof(grid));
        pre_x = pre_y = -1;
        m_note = 0;
        timer = new QTimer();
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeChange()));
    }
    ~Logic();
    void processFile(FILE *file, int time);
    void saveToFile();
    void loadLevel(int level);
public slots:
    void generateEasyGame();
    void generateNormalGame();
    void generateHardGame();
    void noteMode();
    void revoke();
    int check();
    int simpleCheck();
    void clear();
    void pause();
    void recover();
    void newSolver();
    void solveByComputer();
    void solveByPeople();
    void hint();
    void timeChange();
    void restart();
    void showAnswer();
    void setBoardAvailable(int flag);
private:
    void clearNotes(int x, int y);
    void process(const Operation &x, int toShow = 1);
    int pushNumber(int);
    void updateFrame();
    int pushPos(int x, int y);
    std::vector<int> notes[10][10];   // the notes
    int grid[10][10];           // to solve the current state
    int used[10][10];           // whether its for the user to put
    int ans[10][10];
    int generate(int step = 0); // to generate a random sudoku with step empitys;
    int selfCheck(); // only one solution;
    int m_note;         // whether cuurently its note mode;
    MainWindow *window;
    int pre_x, pre_y;
    std::vector<Operation> operations;
    std::vector<Operation> revoked;
    int paused;
    int timeUsed;
    QTimer* timer;
};

#endif // LOGIC_H
