#include "levelitemwidget.h"
#include "ui_levelitemwidget.h"

LevelItemWidget::LevelItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelItemWidget)
{
    ui->setupUi(this);
}

LevelItemWidget::~LevelItemWidget()
{
    delete ui;
}
