#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>
#include <QSoundEffect>

#include "flowboardcontroller.h"
#include "flowcontextcontroller.h"
#include "globalconstant.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    FlowBoardController *m_board;
    FlowContextController *m_game;

    QSound *m_sound_won,
           *m_sound_broke,
           *m_sound_connected,
           *m_sound_click;

public slots:
    void movesChanged(int moves);
    void ratioChanged(double ratio);

    void shouldDoSolve(void);
    void shouldDoRestart(void);
    void shouldDoRandom(void);
    void shouldDoNextLevel(void);
    void shouldDoGameWon(void);
    void shouldPrepareForGame(void);

};

#endif // MAINWINDOW_H
