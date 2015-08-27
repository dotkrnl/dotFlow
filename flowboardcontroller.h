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

    FlowBoard *getBoard(void) { return m_board; }
    int getBest(int level) { return m_best[level]; }
    bool getPerfect(int level) { return m_perfect[level]; }

protected:
    QVector<QString> m_files;
    FlowBoard *m_board;
    int m_current;

    void setBest(int level, int value, bool perfect);

private:
    QVector<int> m_best;
    QVector<bool> m_perfect;

signals:
    void bestChanged(int level, int value, bool perfect);

public slots:
    void previous(void);
    void next(void);
    void restart(void);
    void select(int level);
    void updateBest(int best, bool perfect);

};

#endif // FLOWBOARDCONTROLLER_H
