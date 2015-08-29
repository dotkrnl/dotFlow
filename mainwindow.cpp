#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_sound_won(new QSound(":/sound/res/won.wav", this)),
    m_sound_broke(new QSound(":/sound/res/broke.wav", this)),
    m_sound_connected(new QSound(":/sound/res/connected.wav", this)),
    m_sound_click(new QSound(":/sound/res/click.wav", this)),
    m_solved(false)
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
    connect(ui->solveButton, SIGNAL(pressed()),
            this, SLOT(shouldDoSolve()));
    connect(ui->solveButton, SIGNAL(released()),
            this, SLOT(shouldUndoSolve()));

    connect(ui->winWidget, SIGNAL(randomLevelClicked()),
            this, SLOT(shouldDoRandom()));
    connect(ui->winWidget, SIGNAL(nextLevelClicked()),
            this, SLOT(shouldDoNextLevel()));
    connect(ui->winWidget, SIGNAL(restartLevelClicked()),
            this, SLOT(shouldDoRestart()));

    connect(ui->levelWidget, SIGNAL(selected(int)),
            m_board, SLOT(select(int)));
    connect(ui->levelWidget, SIGNAL(restartClicked()),
            this, SLOT(shouldDoRestart()));
    connect(ui->levelWidget, SIGNAL(randomClicked()),
            this, SLOT(shouldDoRandom()));
    connect(ui->levelWidget, SIGNAL(loadClicked()),
            m_board, SLOT(loadExternal()));
    connect(ui->levelWidget, SIGNAL(resetClicked()),
            this, SLOT(shouldDoReset()));

    connect(ui->hintsWidget, SIGNAL(dismissed()),
            this, SLOT(hintsDismissed()));
    connect(m_board, SIGNAL(gameInitialized()),
            ui->hintsWidget, SLOT(show()));

    // sound configuration
    connect(ui->levelButton, SIGNAL(clicked(bool)),
            m_sound_click, SLOT(play()));
    connect(ui->undoButton, SIGNAL(clicked(bool)),
            m_sound_click, SLOT(play()));
    connect(ui->solveButton, SIGNAL(pressed()),
            m_sound_click, SLOT(play()));
    connect(ui->winWidget, SIGNAL(randomLevelClicked()),
            m_sound_click, SLOT(play()));
    connect(ui->winWidget, SIGNAL(restartLevelClicked()),
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
    m_elapsed.start();
    m_game->solve(m_solved = !m_solved);
}

void MainWindow::shouldUndoSolve(void)
{
    if (m_elapsed.elapsed() > 200)
        m_game->solve(m_solved = false);
}

void MainWindow::shouldDoRestart(void)
{
    m_board->restart();
}

void MainWindow::shouldDoRandom(void)
{
    m_elapsed.start();
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
    bool perfect = m_board->getPerfect()
            && m_board->getBest() == m_game->getMoves();
    ui->winWidget->setBest(m_board->getBest(), perfect);
    ui->winWidget->show();
}

void MainWindow::shouldDoReset(void)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
                this, "Danger!", "Are you sure to reset game saves?",
                QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        m_board->initGame();
    }
}

void MainWindow::shouldPrepareForGame(void)
{
    ui->winWidget->hide();
    ui->levelWidget->hide();
}

void MainWindow::hintsDismissed(void)
{
    if (m_board->current() == 0)
        m_game->linkForFirstLevel();
}
