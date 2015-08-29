#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>
#include <QSoundEffect>
#include <QMessageBox>
#include <QTime>

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

    QTime m_elapsed;
    bool m_solved;

public slots:
    void movesChanged(int moves);
    void ratioChanged(double ratio);

    void shouldDoSolve(void);
    void shouldUndoSolve(void);
    void shouldDoRestart(void);
    void shouldDoRandom(void);
    void shouldDoNextLevel(void);
    void shouldDoGameWon(void);
    void shouldDoReset(void);
    void shouldPrepareForGame(void);

    void hintsDismissed(void);

};

#endif // MAINWINDOW_H
