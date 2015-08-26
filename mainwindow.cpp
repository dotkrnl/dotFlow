#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_board(new FlowBoard(this)),
    m_sound_won(new QSound(":/sound/res/won.wav", this)),
    m_sound_broke(new QSound(":/sound/res/broke.wav", this)),
    m_sound_connected(new QSound(":/sound/res/connected.wav", this))
{
    ui->setupUi(this);
    setCursor(QCursor(Qt::CrossCursor));

    // TODO
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

    connect(m_controller, SIGNAL(gameWon()),
            this, SLOT(gameWon()));
    connect(m_controller, SIGNAL(flowTruncated()),
            this, SLOT(flowBroke()));
    connect(m_controller, SIGNAL(flowAddedWithoutTruncation()),
            this, SLOT(flowConnected()));

    connect(ui->restartButton, SIGNAL(clicked(bool)),
            this, SLOT(restartClicked()));
    connect(ui->restartButtonInWin, SIGNAL(clicked(bool)),
            this, SLOT(restartClicked()));
    connect(ui->undoButton, SIGNAL(clicked(bool)),
            m_controller, SLOT(undo()));

    ui->winWidget->hide();

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, FLOW_BACKGROUND);
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
    ui->winWidget->hide();

    // TODO
    QFile file(":/gameinfo/res/5x5/1");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    m_board->loadFrom(&file);
}

void MainWindow::flowBroke(void)
{
    m_sound_broke->play();
}

void MainWindow::flowConnected(void)
{
    m_sound_connected->play();
}

void MainWindow::gameWon(void)
{
    m_sound_won->play();
    ui->moveCountInWin->setText(QString::number(m_controller->getMoves()));
    ui->winWidget->show();
}
