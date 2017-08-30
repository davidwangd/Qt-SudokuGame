#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <QSignalMapper>
#include <QMessageBox>
#include "logic.h"
#include <QKeyEvent>
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
        number[i]->installEventFilter(this);
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
            grid[i][j]->installEventFilter(this);
            connect(grid[i][j], SIGNAL(clicked()), mapper, SLOT(map()));
            mapper->setMapping(grid[i][j], 10+i*9+j);
        }
    }

    for (int i = 1;i <= 10;i++){
        actionLevel[i] = new QAction(ui->menuLevelGame);
        ui->menuLevelGame->addAction(actionLevel[i]);
        actionLevel[i]->setText("Level" + QString::number(i));
        connect(actionLevel[i], SIGNAL(triggered()), mapper, SLOT(map()));
        mapper -> setMapping(actionLevel[i], -i);
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
    if (number < 0){
        logic -> loadLevel(-number);
    }
    if (number < 10) logic -> pushNumber(number);
    else{
        number -= 10;
        int x = number / 9;
        int y = number % 9;
        logic -> pushPos(x, y);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    logic -> saveToFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    int x = event -> key();
    if ('0' <= x && x <= '9'){
        logic -> pushNumber(x - '0');
    }
    return QMainWindow::keyPressEvent(event);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *eve){
    if (eve -> type() == QEvent::KeyPress){
        QKeyEvent* event = (QKeyEvent *)eve;
        if (event -> key() == Qt::Key_Left){
            logic -> pushPos((logic -> pre_x), (logic -> pre_y - 1 + SIZE)%SIZE);
            return true;
        }else if (event -> key() == Qt::Key_Right){
            logic -> pushPos((logic -> pre_x), (logic -> pre_y + 1)%SIZE);
            return true;
        }else if (event -> key() == Qt::Key_Up){
            logic -> pushPos((logic -> pre_x + SIZE - 1) % SIZE, (logic -> pre_y));
            return true;
        }else if (event -> key() == Qt::Key_Down){
            logic -> pushPos((logic -> pre_x + 1) % SIZE, (logic -> pre_y));
            return true;
        }
        return false;
    }
    return false;
}
