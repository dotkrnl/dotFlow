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
#include "flowglobal.h"

class FlowGameView : public QWidget
{
    Q_OBJECT

public:
    explicit FlowGameView(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    FlowBoard *m_board;
    FlowContext *m_context;

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
    void drawContextBoard(QPainter &painter);

    void drawDot(QPainter &painter, QPoint dot, int color);
    void drawRoundedLine(QPainter &painter, QPoint f, QPoint t, int color);
    void drawRound(QPainter &painter, QPoint center, int diameter);

    void drawMouse(QPainter &painter);

signals:

public slots:
    void boardChanged(void);
    void contextChanged(void);
    void mouseColorChanged(int color);

};

#endif // FLOWGAMEVIEW_H
