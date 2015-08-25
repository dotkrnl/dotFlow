#ifndef FLOWCONTEXT_H
#define FLOWCONTEXT_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include "flowboard.h"

typedef QVector<QPoint> PointSeries;

class FlowContext : public QObject
{
    Q_OBJECT

public:
    explicit FlowContext(FlowBoard *mother, QObject *parent = 0);
    void addRoute(int color, PointSeries route);
    void cloneTo(FlowContext &dest, bool update = true);

    int getColorAt(QPoint location);
    PointSeries getRouteOf(int color);

protected:
    QVector<PointSeries> m_context;
    FlowBoard *m_board;

signals:
    void contextUpdated(void);

public slots:
    void initFlowContext(int color_count);

};

#endif // FLOWCONTEXT_H
