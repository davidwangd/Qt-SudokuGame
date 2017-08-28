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