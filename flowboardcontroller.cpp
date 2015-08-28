#include "flowboardcontroller.h"

#include <QDebug>

FlowBoardController::FlowBoardController(QObject *parent)
    : QObject(parent),
      m_board(new FlowBoard(this)),
      m_settings(new QSettings(this))
{
    QDirIterator it(GAMEINFO_DIR);
    while (it.hasNext())
        m_files.append(it.next());
    qSort(m_files);

    if (m_settings->value("board_total", 0).toInt()
            != m_files.size())
        initGame();

    connect(this, SIGNAL(levelChanged(int)),
            this, SLOT(loadBoard()));

    select(m_settings->value("last_level", 0).toInt());
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

int randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

void FlowBoardController::random(void)
{
    select(randInt(0, total()));
}

void FlowBoardController::select(int level)
{
    if (level < 0) select(0);
    else if (level >= total()) select(total() - 1);
    else {
        emit levelChanged(m_current = level);
        m_settings->setValue("last_level", level);
        m_settings->sync();
    }
}

void FlowBoardController::initGame(void)
{
    m_settings->setValue("board_total", total());
    m_settings->sync();
    for (int i = 0; i < total(); i++)
        setBest(i, 0, false);
    select(0);
    emit gameInitialized();
}

int FlowBoardController::getBest(void)
{
    return getBest(current());
}

bool FlowBoardController::getPerfect(void)
{
    return getPerfect(current());
}

int FlowBoardController::getBest(int level)
{
    QString sl = QString::number(level);
    return m_settings->value("board_best/" + sl, 0).toInt();
}

bool FlowBoardController::getPerfect(int level)
{
    QString sl = QString::number(level);
    return m_settings->value("board_perfect/" + sl, false).toBool();
}

void FlowBoardController::setBest(int level, int value, bool perfect)
{
    QString sl = QString::number(level);
    m_settings->setValue("board_best/" + sl, value);
    m_settings->setValue("board_perfect/" + sl, perfect);
    m_settings->sync();
    emit bestChanged(level, value, perfect);
}

void FlowBoardController::updateBest(int best, bool perfect)
{
    int b = getBest(current());
    if (b == 0 || b > best)
        setBest(current(), best, perfect);
}

void FlowBoardController::loadBoard(void)
{
    QFile file(m_files[current()]);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    m_board->loadFrom(&file);
}
