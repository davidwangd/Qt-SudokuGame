#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "debug.h"
#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include "const.h"

namespace Ui {
class MainWindow;
}
class Logic;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class Logic;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void numberPressed(int);
private:
    QPushButton *number[10];
    QPushButton *grid[10][10];
    QPushButton *test;
    enum{
        size = 55,
        padding = 10
    };
    Ui::MainWindow *ui;
    QSignalMapper *mapper;
    Logic *logic;
};

#endif // MAINWINDOW_H
