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
    FlowContext *getDisplayContext(void);

protected:
    // TODO: undo function.
    FlowContext *m_stable;
    FlowContext *m_beta;

    FlowBoard *m_board;

    int m_current_color;
    PointSeries m_current_route;

signals:

public slots:
    void initFlowContext(int color_count);
    void startRoute(QPoint location);
    void newRoutePoint(QPoint location);
    void endRoute(void);

};

#endif // FLOWCONTEXTCONTROLLER_H
