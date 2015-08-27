#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>

namespace Ui {
class LevelWidget;
}

class LevelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LevelWidget(QWidget *parent = 0);
    ~LevelWidget();

private:
    Ui::LevelWidget *ui;
};

#endif // LEVELWIDGET_H
