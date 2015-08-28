#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_sound_won(new QSound(":/sound/res/won.wav", this)),
    m_sound_broke(new QSound(":/sound/res/broke.wav", this)),
    m_sound_connected(new QSound(":/sound/res/connected.wav", this)),
    m_sound_click(new QSound(":/sound/res/click.wav", this))
{
    ui->setupUi(this);
    setCursor(QCursor(Qt::CrossCursor));

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, FLOW_BACKGROUND);
    this->setPalette(Pal);

    m_board = new FlowBoardController(this);

    FlowBoard *gameboard = m_board->getBoard();
    m_game = new FlowContextController(gameboard, this);

    ui->gameWidget->useBoard(gameboard);
    ui->gameWidget->useContextController(m_game);

    ui->levelWidget->useBoardController(m_board);

    connect(m_game, SIGNAL(movesChanged(int)),
            this, SLOT(movesChanged(int)));
    connect(m_game, SIGNAL(movesChanged(int)),
            ui->winWidget, SLOT(setMoves(int)));
    connect(m_game, SIGNAL(realTimeRatioChanged(double)),
            this, SLOT(ratioChanged(double)));

    connect(m_board->getBoard(), SIGNAL(boardLoaded(int)),
            this, SLOT(shouldPrepareForGame()));

    connect(m_game, SIGNAL(gameWon()),
            this, SLOT(shouldDoGameWon()));
    connect(m_game, SIGNAL(flowTruncated()),
            m_sound_broke, SLOT(play()));
    connect(m_game, SIGNAL(flowAddedWithoutTruncation()),
            m_sound_connected, SLOT(play()));

    connect(ui->levelButton, SIGNAL(clicked(bool)),
            ui->levelWidget, SLOT(show()));
    connect(ui->undoButton, SIGNAL(clicked(bool)),
            m_game, SLOT(undo()));
    connect(ui->solveButton, SIGNAL(clicked(bool)),
            this, SLOT(shouldDoSolve()));

    connect(ui->winWidget, SIGNAL(randomLevelClicked()),
            this, SLOT(shouldDoRandom()));
    connect(ui->winWidget, SIGNAL(nextLevelClicked()),
            this, SLOT(shouldDoNextLevel()));

    connect(ui->levelWidget, SIGNAL(selected(int)),
            m_board, SLOT(select(int)));
    connect(ui->levelWidget, SIGNAL(restartClicked()),
            this, SLOT(shouldDoRestart()));
    connect(ui->levelWidget, SIGNAL(randomClicked()),
            this, SLOT(shouldDoRandom()));
    connect(ui->levelWidget, SIGNAL(resetClicked()),
            m_board, SLOT(initGame()));

    connect(m_board, SIGNAL(levelChanged(int)),
            m_game, SLOT(linkForFirstLevel(int)));
    m_game->linkForFirstLevel(m_board->current());
    connect(m_board, SIGNAL(gameInitialized()),
            ui->hintsWidget, SLOT(show()));

    // sound configuration
    connect(ui->levelButton, SIGNAL(clicked(bool)),
            m_sound_click, SLOT(play()));
    connect(ui->undoButton, SIGNAL(clicked(bool)),
            m_sound_click, SLOT(play()));
    connect(ui->solveButton, SIGNAL(clicked(bool)),
            m_sound_click, SLOT(play()));
    connect(ui->winWidget, SIGNAL(randomLevelClicked()),
            m_sound_click, SLOT(play()));
    connect(ui->winWidget, SIGNAL(nextLevelClicked()),
            m_sound_click, SLOT(play()));
    connect(ui->levelWidget, SIGNAL(selected(int)),
            m_sound_click, SLOT(play()));
    connect(ui->levelWidget, SIGNAL(hideClicked()),
            m_sound_click, SLOT(play()));
    connect(ui->levelWidget, SIGNAL(restartClicked()),
            m_sound_click, SLOT(play()));
    connect(ui->levelWidget, SIGNAL(randomClicked()),
            m_sound_click, SLOT(play()));

    shouldPrepareForGame();
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

void MainWindow::shouldDoSolve(void)
{
    m_game->solve();
}

void MainWindow::shouldDoRestart(void)
{
    m_board->restart();
}

void MainWindow::shouldDoRandom(void)
{
    m_board->random();
}

void MainWindow::shouldDoNextLevel(void)
{
    m_board->next();
}

void MainWindow::shouldDoGameWon(void)
{
    m_sound_won->play();
    m_board->updateBest(m_game->getMoves(),
        m_game->getMoves() == m_board->getBoard()->getColorCount());
    ui->winWidget->setBest(m_board->getBest());
    ui->winWidget->show();
}

void MainWindow::shouldPrepareForGame(void)
{
    ui->winWidget->hide();
    ui->levelWidget->hide();
}
