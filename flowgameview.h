#ifndef FLOWGAMEVIEW_H
#define FLOWGAMEVIEW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
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

    bool m_pressed;
    QPoint m_mouse_pos;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    FlowBoard *m_board;

    // common information for quick access
    int m_col, m_line, m_ppc, m_ppl;
    int m_wzero, m_hzero;  // zero location
    int m_width, m_height; // usable size
    // recalculate common info when required
    void recalculateCommonSize(void);
    QPoint resolveLocation(QPoint mouse);

    void drawBoard(QPainter &painter);
    void drawDots(QPainter &painter);
    void drawDot(QPainter &painter, QPoint dot);
    void drawMouse(QPainter &painter);

signals:

public slots:
    void boardChanged(void);

};

#endif // FLOWGAMEVIEW_H
