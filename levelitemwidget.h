#ifndef LEVELITEMWIDGET_H
#define LEVELITEMWIDGET_H

#include <QWidget>

namespace Ui {
class LevelItemWidget;
}

class LevelItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LevelItemWidget(QWidget *parent = 0);
    ~LevelItemWidget();

private:
    Ui::LevelItemWidget *ui;
};

#endif // LEVELITEMWIDGET_H
