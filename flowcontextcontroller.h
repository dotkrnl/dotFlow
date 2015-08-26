#ifndef FLOWCONTEXTCONTROLLER_H
#define FLOWCONTEXTCONTROLLER_H

#include <QObject>
#include <QPoint>
#include "flowcontext.h"

class FlowContextController : public QObject
{
    Q_OBJECT

public:
    explicit FlowContextController(FlowBoard *mother, QObject *parent = 0);
    FlowContext *getDisplayContext(void) { return m_beta; }

    int getMoves(void) { return m_moves; }

protected:
    FlowBoard *m_board;

    // TODO: undo function.
    FlowContext *m_stable;
    FlowContext *m_beta;

    PointSeries m_current_route;

    void setCurrentColor(int color);
    void setMoves(int moves);

    int getCurrentColor(void) { return m_current_color; }

private:
    bool isTerminalDotsOfOthers(QPoint location);
    void truncateCurrentRoute(QPoint terminal);
    bool isNearTheEndOfRoute(QPoint location);
    bool isOutOfTerminal(QPoint location);
    bool isInRange(QPoint location);

    int m_current_color;
    int m_previous_legal_color;
    int m_moves;

signals:
    void colorChanged(int color);
    void movesChanged(int moves);
    void realTimeRatioChanged(double ratio);
    void gameWon(void);

public slots:
    void restart(void);

    void startRoute(QPoint location);
    void newRoutePoint(QPoint location);
    void endRoute(void);

    void betaRatioChanged(double ratio);
    void stableRatioChanged(double ratio);
};

#endif // FLOWCONTEXTCONTROLLER_H
