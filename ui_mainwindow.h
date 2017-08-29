/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEasy;
    QAction *actionNormal;
    QAction *actionHard;
    QAction *actionExit;
    QAction *actionSimpleCheck;
    QAction *actionCheck;
    QAction *actionHint;
    QAction *actionShow_Answer;
    QWidget *centralWidget;
    QFrame *mainFrame;
    QFrame *buttonFrame;
    QPushButton *btnRevoke;
    QPushButton *btnNoteMode;
    QPushButton *btnClear;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QMenu *menuCheating;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(694, 699);
        actionEasy = new QAction(MainWindow);
        actionEasy->setObjectName(QStringLiteral("actionEasy"));
        actionNormal = new QAction(MainWindow);
        actionNormal->setObjectName(QStringLiteral("actionNormal"));
        actionHard = new QAction(MainWindow);
        actionHard->setObjectName(QStringLiteral("actionHard"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSimpleCheck = new QAction(MainWindow);
        actionSimpleCheck->setObjectName(QStringLiteral("actionSimpleCheck"));
        actionCheck = new QAction(MainWindow);
        actionCheck->setObjectName(QStringLiteral("actionCheck"));
        actionHint = new QAction(MainWindow);
        actionHint->setObjectName(QStringLiteral("actionHint"));
        actionShow_Answer = new QAction(MainWindow);
        actionShow_Answer->setObjectName(QStringLiteral("actionShow_Answer"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mainFrame = new QFrame(centralWidget);
        mainFrame->setObjectName(QStringLiteral("mainFrame"));
        mainFrame->setGeometry(QRect(20, 20, 531, 531));
        mainFrame->setFrameShape(QFrame::StyledPanel);
        mainFrame->setFrameShadow(QFrame::Raised);
        buttonFrame = new QFrame(centralWidget);
        buttonFrame->setObjectName(QStringLiteral("buttonFrame"));
        buttonFrame->setGeometry(QRect(570, 20, 101, 611));
        buttonFrame->setFrameShape(QFrame::StyledPanel);
        buttonFrame->setFrameShadow(QFrame::Raised);
        btnRevoke = new QPushButton(centralWidget);
        btnRevoke->setObjectName(QStringLiteral("btnRevoke"));
        btnRevoke->setGeometry(QRect(50, 570, 161, 31));
        btnNoteMode = new QPushButton(centralWidget);
        btnNoteMode->setObjectName(QStringLiteral("btnNoteMode"));
        btnNoteMode->setGeometry(QRect(260, 570, 131, 31));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        btnNoteMode->setFont(font);
        btnClear = new QPushButton(centralWidget);
        btnClear->setObjectName(QStringLiteral("btnClear"));
        btnClear->setGeometry(QRect(430, 570, 101, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 694, 26));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        menuCheating = new QMenu(menuBar);
        menuCheating->setObjectName(QStringLiteral("menuCheating"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuBar->addAction(menuCheating->menuAction());
        menuGame->addAction(actionEasy);
        menuGame->addAction(actionNormal);
        menuGame->addAction(actionHard);
        menuGame->addSeparator();
        menuGame->addAction(actionExit);
        menuCheating->addAction(actionSimpleCheck);
        menuCheating->addAction(actionCheck);
        menuCheating->addAction(actionHint);
        menuCheating->addSeparator();
        menuCheating->addAction(actionShow_Answer);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Sudoku Game 0.0.1 beta", 0));
        actionEasy->setText(QApplication::translate("MainWindow", "New Easy Game", 0));
        actionNormal->setText(QApplication::translate("MainWindow", "New Normal Game", 0));
        actionHard->setText(QApplication::translate("MainWindow", "New Hard Game", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionSimpleCheck->setText(QApplication::translate("MainWindow", "Simple Check", 0));
        actionCheck->setText(QApplication::translate("MainWindow", "Check", 0));
        actionHint->setText(QApplication::translate("MainWindow", "Hint", 0));
        actionShow_Answer->setText(QApplication::translate("MainWindow", "Show Answer", 0));
        btnRevoke->setText(QApplication::translate("MainWindow", "Revoke", 0));
        btnNoteMode->setText(QApplication::translate("MainWindow", "note mode", 0));
        btnClear->setText(QApplication::translate("MainWindow", "clear", 0));
        menuGame->setTitle(QApplication::translate("MainWindow", "Sudoku Game", 0));
        menuCheating->setTitle(QApplication::translate("MainWindow", "Cheating", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
