#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <QSignalMapper>
#include "logic.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    logic(new Logic(this))
{
    static char buffer[100];
    ui->setupUi(this);
    mapper = new QSignalMapper(this);
    for (int i = 1;i < 10;i++){
        sprintf(buffer, "%d", i);
        number[i] = new QPushButton(buffer, ui->buttonFrame);
        number[i]->setGeometry(padding, padding * (i) + size * (i-1), size, size);
        number[i]->show();
        connect(number[i], SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(number[i], i);
    }

    // right x increase
    // down y increase..
    for (int i = 0;i < 9;i++){
        for (int j = 0;j < 9;j++){
            grid[i][j] = new QPushButton(ui->mainFrame);
            grid[i][j]->setGeometry(padding * (j/3+1) + size * j, padding*(i/3+1) + size * i, size, size);
            grid[i][j]->show();
            connect(grid[i][j], SIGNAL(clicked()), mapper, SLOT(map()));
            mapper->setMapping(grid[i][j], 10+i*9+j);
        }
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(numberPressed(int)));
    connect(ui->btnRevoke, SIGNAL(clicked()), logic, SLOT(revoke()));
    connect(ui->btnNoteMode, SIGNAL(clicked()), logic, SLOT(noteMode()));
    connect(ui->btnClear, SIGNAL(clicked()), logic, SLOT(clear()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionEasy, SIGNAL(triggered()), logic, SLOT(generateEasyGame()));
    connect(ui->actionNormal, SIGNAL(triggered()), logic, SLOT(generateNormalGame()));
    connect(ui->actionHard, SIGNAL(triggered()), logic, SLOT(generateHardGame()));
    connect(ui->actionCheck, SIGNAL(triggered()), logic, SLOT(check()));
    connect(ui->actionSimpleCheck, SIGNAL(triggered()), logic, SLOT(simpleCheck()));
    connect(ui->actionHard, SIGNAL(triggered()), logic, SLOT(hint()));
    connect(ui->btnRecover, SIGNAL(clicked()), logic, SLOT(recover()));
    connect(ui->actionRestart, SIGNAL(triggered()), logic, SLOT(restart()));
    connect(ui->btnPause, SIGNAL(clicked()), logic, SLOT(pause()));
    connect(ui->actionHint, SIGNAL(triggered()), logic, SLOT(hint()));
    connect(ui->actionNewSolver, SIGNAL(triggered()), logic, SLOT(newSolver()));
    connect(ui->actionSolveByPeople, SIGNAL(triggered()), logic, SLOT(solveByPeople()));
    connect(ui->actionSolveByComputer, SIGNAL(triggered()), logic, SLOT(solveByComputer()));
    connect(ui->actionShow_Answer, SIGNAL(triggered()), logic, SLOT(showAnswer()));
    FILE *file;
    file = fopen("soduku.game", "r");
    int time;
    if (file == NULL || (fscanf(file, "%d", &time) == EOF)){
        file = fopen("soduku.game", "w");
        for (int i = 0;i < SIZE;i++)
            for (int j = 0;j < SIZE;j++)
                grid[i][j] -> setEnabled(false);
    }else{
        logic -> processFile(file, time);
    }
}

void MainWindow::numberPressed(int number){
#ifdef DEBUG
    printf("numberPressed(%d)\n", number);
#endif
    if (number < 10) logic -> pushNumber(number);
    else{
        number -= 10;
        int x = number / 9;
        int y = number % 9;
        logic -> pushPos(x, y);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
