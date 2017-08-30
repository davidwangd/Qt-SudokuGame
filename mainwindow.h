#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "debug.h"
#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include "const.h"
#include <QAction>
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
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
public slots:
    void numberPressed(int);
private:
    QPushButton *number[10];
    QPushButton *grid[10][10];
    QPushButton *test;
    QAction *actionLevel[15];
    enum{
        size = 55,
        padding = 10
    };
    Ui::MainWindow *ui;
    QSignalMapper *mapper;
    Logic *logic;
};

#endif // MAINWINDOW_H
