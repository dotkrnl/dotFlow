#ifndef LEVELITEMWIDGET_H
#define LEVELITEMWIDGET_H

#include <QWidget>
#include <cstdlib>

namespace Ui {
class LevelItemWidget;
}

class LevelItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LevelItemWidget(int level, QWidget *parent = 0);
    ~LevelItemWidget();

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::LevelItemWidget *ui;
    int m_level;

    void setBestCount(int best);
    void displayID();

signals:
    void selected(void);

public slots:
    void setBest(int level, int value, bool perfect);

};

#endif // LEVELITEMWIDGET_H
