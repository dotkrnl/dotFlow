#ifndef FLOWCONTEXTCONTROLLER_H
#define FLOWCONTEXTCONTROLLER_H

#include <QObject>
#include <QStack>
#include <QPoint>

#include "flowcontext.h"
#include "flowsolver.h"
#include "globalconstant.h"

class FlowContextController : public QObject
{
    Q_OBJECT

public:
    explicit FlowContextController(FlowBoard *mother, QObject *parent = 0);
    FlowContext *getDisplayContext(void) { return m_beta; }
    FlowContext *getBoardContext(void) { return m_stable; }

    int getMoves(void) { return m_moves; }

protected:
    FlowBoard *m_board;
    FlowSolver *m_solver;

    QStack<FlowContext *> m_undo;
    FlowContext *m_stable;
    FlowContext *m_beta;

    PointSeries m_current_route;

    void setCurrentColor(int color);
    void setMoves(int moves);

    int getCurrentColor(void) { return m_current_color; }

private:
    bool isTerminalDotsOfOthers(QPoint location);
    void truncateCurrentRoute(QPoint terminal);
    bool makeReachableBy(QPoint from, QPoint to, int depth);
    bool isOutOfTerminal(QPoint location);
    bool isInRange(QPoint location);

    int m_current_color;
    int m_previous_legal_color;
    int m_moves;

signals:
    void colorChanged(int color);
    void movesChanged(int moves);
    void realTimeRatioChanged(double ratio);

    void flowTruncated(void);
    void flowAddedWithoutTruncation(void);
    void gameWon(void);

public slots:
    void solve(void);
    void restart(void);
    void undo(void);

    void startRoute(QPoint location);
    void newRoutePoint(QPoint location);
    void endRoute(void);

    void stableRatioChanged(double ratio);
    void linkForFirstLevel(void);
};

#endif // FLOWCONTEXTCONTROLLER_H
