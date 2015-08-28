#ifndef LEVELWIDGET_H
#define LEVELWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QScrollBar>
#include <QAbstractItemView>
#include <QSignalMapper>

#include "levelitemwidget.h"
#include "flowboardcontroller.h"

namespace Ui {
class LevelWidget;
}

class LevelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LevelWidget(QWidget *parent = 0);
    ~LevelWidget();

    void useBoardController(FlowBoardController *b);

protected:
    void showEvent(QShowEvent *event);

private:
    Ui::LevelWidget *ui;
    FlowBoardController *m_board;
    QSignalMapper *m_select_mapper;

signals:
    void selected(int level);
    void hideClicked(void);
    void restartClicked(void);
    void randomClicked(void);
    void resetClicked(void);

};

#endif // LEVELWIDGET_H
