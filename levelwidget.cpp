#include "levelwidget.h"
#include "ui_levelwidget.h"

LevelWidget::LevelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelWidget)
{
    ui->setupUi(this);
}

LevelWidget::~LevelWidget()
{
    delete ui;
}
