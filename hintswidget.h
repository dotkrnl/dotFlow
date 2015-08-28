#ifndef HINTSWIDGET_H
#define HINTSWIDGET_H

#include <QWidget>

namespace Ui {
class HintsWidget;
}

class HintsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HintsWidget(QWidget *parent = 0);
    ~HintsWidget();

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::HintsWidget *ui;

signals:
    void dismissed(void);
};

#endif // HINTSWIDGET_H
