#ifndef FLOWGAMEVIEW_H
#define FLOWGAMEVIEW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>

#include <cmath>

#include "flowboard.h"
#include "flowcontextcontroller.h"
#include "globalconstant.h"

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = 0);

    void useBoard(FlowBoard *board);
    void useContextController(FlowContextController *controller);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    FlowBoard *m_board;
    FlowContext *m_context;
    FlowContext *m_boardcontext;
    FlowContextController *m_controller;

    bool m_pressed;
    QPoint m_mouse_pos;
    int m_mouse_color;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    // common information for quick access
    int m_col, m_line, m_ppc, m_ppl;
    int m_wzero, m_hzero;  // zero location
    int m_width, m_height; // usable size
    int m_relative_size;   // used to calculate relative size
    // recalculate common info when required
    void recalculateCommonSize(void);

    QPoint decodeLocation(QPoint mouse);
    QPoint encodeLocation(QPoint location);

    void drawBoard(QPainter &painter);
    void drawDots(QPainter &painter);
    void drawContext(QPainter &painter);
    void drawBoardContext(QPainter &painter);

    void drawDot(QPainter &painter, QPoint dot, int color);
    void drawRound(QPainter &painter, QPoint center, int diameter);

    void drawMouse(QPainter &painter);

signals:

public slots:
    void boardChanged(void);
    void contextChanged(void);
    void boardcontextChanged(void);
    void mouseColorChanged(int color);

};

#endif // FLOWGAMEVIEW_H
