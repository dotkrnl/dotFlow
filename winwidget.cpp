#include "winwidget.h"
#include "ui_winwidget.h"

WinWidget::WinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinWidget)
{
    ui->setupUi(this);

    connect(ui->nextButton, SIGNAL(clicked(bool)),
            this, SIGNAL(nextLevelClicked()));
    connect(ui->randomButton, SIGNAL(clicked(bool)),
            this, SIGNAL(randomLevelClicked()));
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

void WinWidget::setBest(int best, bool perfect)
{
    ui->bestCount->setText(QString::number(best));
    if (perfect) {
        ui->star_perfect->show();
        ui->restartButton->hide();
        ui->randomButton->show();
    } else {
        ui->star_perfect->hide();
        ui->restartButton->show();
        ui->randomButton->hide();
    }
}
