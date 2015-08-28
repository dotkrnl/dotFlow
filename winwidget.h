#ifndef WINWIDGET_H
#define WINWIDGET_H

#include <QWidget>

namespace Ui {
class WinWidget;
}

class WinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WinWidget(QWidget *parent = 0);
    ~WinWidget();

private:
    Ui::WinWidget *ui;

signals:
    void nextLevelClicked(void);
    void randomLevelClicked(void);
    void restartLevelClicked(void);

public slots:
    void setMoves(int moves);
    void setBest(int best, bool perfect);
};

#endif // WINWIDGET_H
