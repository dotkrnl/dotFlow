#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_board(new FlowBoard(this))
{
    ui->setupUi(this);
    setCursor(QCursor(Qt::CrossCursor));

    QFile file(":/gameinfo/res/5x5/1");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    m_board->loadFrom(&file);
    ui->gameView->useBoard(m_board);

    m_controller = new FlowContextController(m_board, this);
    ui->gameView->useController(m_controller);
    connect(m_controller, SIGNAL(movesChanged(int)),
            this, SLOT(movesChanged(int)));
    connect(m_controller, SIGNAL(realTimeRatioChanged(double)),
            this, SLOT(ratioChanged(double)));

    connect(ui->restartButton, SIGNAL(clicked(bool)),
            this, SLOT(restartClicked()));

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, FLOW_BACKGROUND);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::movesChanged(int moves)
{
    ui->moveCount->setText(QString::number(moves));
}

void MainWindow::ratioChanged(double ratio)
{
    const double EPS = 1E-8;
    int i_ratio = (ratio + EPS) * 100;
    ui->ratioCount->setText(QString::number(i_ratio) + "%");
}

void MainWindow::restartClicked(void)
{
    QFile file(":/gameinfo/res/5x5/1");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    m_board->loadFrom(&file);
}
