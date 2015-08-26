#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "flowboard.h"
#include "flowcontextcontroller.h"
#include "flowglobal.h"

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

    FlowBoard *m_board;
    FlowContextController *m_controller;

public slots:
    void movesChanged(int moves);
    void ratioChanged(double ratio);
    void restartClicked(void);

};

#endif // MAINWINDOW_H
