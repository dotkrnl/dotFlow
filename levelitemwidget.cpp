#include "levelitemwidget.h"
#include "ui_levelitemwidget.h"

LevelItemWidget::LevelItemWidget(int level, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelItemWidget),
    m_level(level)
{
    ui->setupUi(this);

    setBest(level, 0, false);
    displayID();
}

LevelItemWidget::~LevelItemWidget()
{
    delete ui;
}

void LevelItemWidget::setBest(int level, int value, bool perfect)
{
    // TODO: consider using filter
    if (level != m_level) return; // not for this item

    setBestCount(value);

    ui->best_perfect->hide();
    ui->best->hide();
    ui->try_now->hide();
    ui->bestCount->hide();
    ui->star_perfect->hide();
    ui->star_yes->hide();
    ui->star_no->hide();

    if (!value) {
        ui->try_now->show();
        ui->star_no->show();
    } else if (!perfect){
        ui->best->show();
        ui->bestCount->show();
        ui->star_yes->show();
    } else {
        ui->best_perfect->show();
        ui->bestCount->show();
        ui->star_perfect->show();
    }
}

void LevelItemWidget::setLevel(int level)
{
    QString style;
    if (level == m_level)
        style = "background-color: rgba(0, 0, 0, 255);";
    else
        style = "background-color: rgba(20, 21, 22, 240);";
    ui->widget->setStyleSheet(style);
}

void LevelItemWidget::displayID(void)
{
    QString prepend = "";
    if (m_level < 10) prepend = "#0";
    else if (m_level >= 100) prepend = "";
    else prepend = "#";

    ui->id->setText(prepend + QString::number(m_level));
}

void LevelItemWidget::setBestCount(int value)
{
    ui->bestCount->setText(QString::number(value));
}

void LevelItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit selected();
}
