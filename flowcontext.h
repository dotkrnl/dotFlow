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
    FlowContext(const FlowContext &o);

    void addRoute(int color, PointSeries route);
    void cloneTo(FlowContext &dest, bool update = true) const;

    double getRatio(void) const;
    int getColorAt(QPoint location) const;
    PointSeries getRouteOf(int color) const;
    void clearRouteOf(int color);

    bool isTruncatedComparedTo(const FlowContext &ot) const;

protected:
    QVector<PointSeries> m_context;
    FlowBoard *m_board;

signals:
    void contextUpdated(void);
    void contextRatioChanged(double ratio);

public slots:
    void initFlowContext(int color_count);
    void calculateRatio(void);

};

#endif // FLOWCONTEXT_H
