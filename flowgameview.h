#ifndef FLOWGAMEVIEW_H
#define FLOWGAMEVIEW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QPainter>
#include "flowboard.h"
#include "flowglobal.h"

class FlowGameView : public QWidget
{
    Q_OBJECT

public:
    explicit FlowGameView(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    FlowBoard *m_board;

    // common information for quick access
    int m_col, m_line, m_ppc, m_ppl;
    int m_wzero, m_hzero;  // zero location
    int m_width, m_height; // usable size
    // recalculate common info when required
    void recalculateCommonSize(void);

    void drawBoard(QPainter &painter);
    void drawDots(QPainter &painter);
    void drawDot(QPainter &painter, QPoint dot);

signals:

public slots:
    void boardChanged(void);

};

#endif // FLOWGAMEVIEW_H
