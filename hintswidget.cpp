#include "hintswidget.h"
#include "ui_hintswidget.h"

HintsWidget::HintsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HintsWidget)
{
    ui->setupUi(this);
}

HintsWidget::~HintsWidget()
{
    delete ui;
}

void HintsWidget::mouseReleaseEvent(QMouseEvent *event)
{
    hide();
    emit dismissed();
}
