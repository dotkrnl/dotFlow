#include "flowboardcontroller.h"

#include <QDebug>

FlowBoardController::FlowBoardController(QObject *parent)
    : QObject(parent),
      m_board(new FlowBoard(this))
{
    QDirIterator it(GAMEINFO_DIR);
    while (it.hasNext())
        m_files.append(it.next());
    qSort(m_files);

    m_best.resize(m_files.size());
    m_perfect.resize(m_files.size());

    select(0);
}

void FlowBoardController::previous(void)
{
    select(current() - 1);
}

void FlowBoardController::next(void)
{
    select(current() + 1);
}

void FlowBoardController::restart(void)
{
    select(current());
}

void FlowBoardController::select(int level)
{
    if (level < 0) select(0);
    else if (level >= total()) select(total() - 1);
    else {
        m_current = level;
        QFile file(m_files[current()]);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        m_board->loadFrom(&file);
    }
}

void FlowBoardController::setBest(int level, int value, bool perfect)
{
    emit bestChanged(level,
                     m_best[level] = value,
                     m_perfect[level] = perfect);
}

void FlowBoardController::updateBest(int best, bool perfect)
{
    int l = current();
    if (m_best[l] == 0 || m_best[l] > best)
        setBest(l, best, perfect);
}
