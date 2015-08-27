#include "winwidget.h"
#include "ui_winwidget.h"

WinWidget::WinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinWidget)
{
    ui->setupUi(this);

    connect(ui->nextButton, SIGNAL(clicked(bool)),
            this, SIGNAL(nextLevelClicked()));
    connect(ui->restartButton, SIGNAL(clicked(bool)),
            this, SIGNAL(restartLevelClicked()));
}

WinWidget::~WinWidget()
{
    delete ui;
}

void WinWidget::setMoves(int moves)
{
    ui->moveCount->setText(QString::number(moves));
}

void WinWidget::setBest(int best)
{
    ui->bestCount->setText(QString::number(best));
}
