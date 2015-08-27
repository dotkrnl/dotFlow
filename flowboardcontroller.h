#ifndef FLOWBOARDCONTROLLER_H
#define FLOWBOARDCONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDirIterator>

#include "flowglobal.h"
#include "flowboard.h"

class FlowBoardController : public QObject
{
    Q_OBJECT

public:
    explicit FlowBoardController(QObject *parent = 0);

    int current(void) { return m_current; }
    int total(void) { return m_files.size(); }
    FlowBoard *get(void) { return m_board; }

protected:
    QVector<QString> m_files;
    FlowBoard *m_board;
    int m_current;

    void setBest(int level, int value);
    int getBest(int level) { return m_best[level]; }

private:
    QVector<int> m_best;

signals:
    void bestChanged(int level, int value);

public slots:
    void previous(void);
    void next(void);
    void restart(void);
    void select(int level);
    void updateBest(int best);

};

#endif // FLOWBOARDCONTROLLER_H
