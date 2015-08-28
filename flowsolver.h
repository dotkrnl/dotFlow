#ifndef FLOWSOLVER_H
#define FLOWSOLVER_H

#include <QObject>

#include <flowboard.h>
#include <flowcontext.h>

class FlowSolver : public QObject
{
    Q_OBJECT

public:
    explicit FlowSolver(FlowBoard *board, QObject *parent = 0);
    FlowContext solve(void);

private:
    FlowBoard *m_board;

    DotPairVector m_pairs;
    QVector< QVector<int> > m_value;
    QVector< QVector<QPoint> > m_path;

    bool dfs(int c, QPoint loc);
    bool isInRange(QPoint location);


};

#endif // FLOWSOLVER_H
