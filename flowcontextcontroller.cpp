#include "flowcontextcontroller.h"

FlowContextController::FlowContextController(FlowBoard *mother, QObject *parent)
    : QObject(parent),
      m_board(mother),
      m_stable(new FlowContext(mother, this)),
      m_beta(new FlowContext(mother, this)),
      m_previous_legal_color(-1)
{
    connect(m_board, SIGNAL(boardLoaded(int)),
            this, SLOT(restart()));
    connect(m_stable, SIGNAL(contextRatioChanged(double)),
            this, SLOT(stableRatioChanged(double)));
    connect(m_beta, SIGNAL(contextRatioChanged(double)),
            this, SIGNAL(realTimeRatioChanged(double)));
    setCurrentColor(-1);
    setMoves(0);
}

void FlowContextController::restart(void)
{
    setCurrentColor(-1);
    setMoves(0);
    m_previous_legal_color = -1;

    while (m_undo.size())
        delete m_undo.pop();
}

void FlowContextController::undo(void)
{
    if (!m_undo.size()) return;

    setCurrentColor(-1);
    setMoves(getMoves() - 1);
    m_previous_legal_color = -1;

    FlowContext *top = m_undo.pop();
    top->cloneTo(*m_stable);
    top->cloneTo(*m_beta);
    delete top;
}

void FlowContextController::startRoute(QPoint location)
{
    if (!isInRange(location)) return;

    int dot_color = m_board->getColorAt(location);
    int context_color = m_beta->getColorAt(location);
    int color = dot_color != -1 ?
                dot_color : context_color;

    setCurrentColor(color);

    if (getCurrentColor() == -1)
        // on the board
        return;

    // update moves count
    if (getCurrentColor() != m_previous_legal_color) {
        setMoves(getMoves() + 1);
        // save for undo
        m_undo.push(new FlowContext(m_board, this));
        m_stable->cloneTo(*m_undo.top());
    }
    m_previous_legal_color = getCurrentColor();

    if (dot_color != -1)
        // is a terminal
        m_current_route.resize(0);
    else
        // is on a existing route
        m_current_route = m_beta->getRouteOf(color);

    newRoutePoint(location);
}

void FlowContextController::newRoutePoint(QPoint location)
{
    if (getCurrentColor() == -1) return;
    if (!isInRange(location)) return;

    // don't link to terminal dots of other colors
    if (isTerminalDotsOfOthers(location)) return;

    truncateCurrentRoute(location);

    if (m_current_route.size() == 0)
        // first time or over-truncated?
        m_current_route.append(location);
    else if (!isOutOfTerminal(location)) {
        // or satisfy the conditions to complete route
        for (int i = 1; i <= MAX_FIND_ROUTE; i++)
            if (makeReachableBy(m_current_route.back(), location, i)) {
                m_current_route.append(location);
                break;
            }
    }

    m_stable->cloneTo(*m_beta, false); // update later
    m_beta->addRoute(getCurrentColor(), m_current_route);
    // i.e. addRoute here will update view
}

void FlowContextController::endRoute(void)
{
    if (m_beta->isTruncatedComparedTo(*m_stable))
        emit flowTruncated();
    else if (m_current_route.size() > 1 &&
             m_board->getColorAt(m_current_route.back())
                == m_current_color)
        emit flowAddedWithoutTruncation();

    setCurrentColor(-1);
    m_beta->cloneTo(*m_stable);
}

void FlowContextController::stableRatioChanged(double ratio)
{
    const double EPS = 1E-8;
    if (ratio > 1 - EPS)
        emit gameWon();
}

void FlowContextController::linkForFirstLevel(int level)
{
    // TODO: use game solver
    if (level == 0) {
        startRoute(QPoint(0, 0));
        newRoutePoint(QPoint(2, 0));
        endRoute();

        startRoute(QPoint(0, 2));
        newRoutePoint(QPoint(2, 2));
        endRoute();
    }
}

/*
 * Utility functions
 */

bool FlowContextController::isTerminalDotsOfOthers(QPoint location)
{
    int dot_color = m_board->getColorAt(location);
    return dot_color != -1 && dot_color != getCurrentColor();
}

void FlowContextController::truncateCurrentRoute(QPoint terminal)
{
    for (int i = 0; i < m_current_route.size(); i++) {
        if (terminal == m_current_route[i])
            m_current_route.resize(i);
    }
}

bool FlowContextController::makeReachableBy(QPoint f, QPoint t, int depth)
{
    if (depth <= 0) return false;

    static const int MOVE_TYPE = 4;
    static const QPoint MOVE[4] = {
        QPoint(1, 0), QPoint(-1, 0),
        QPoint(0, 1), QPoint(0, -1),
    };

    for (int i = 0; i < MOVE_TYPE; i++)
        if (f + MOVE[i] == t) return true;

    for (int i = 0; i < MOVE_TYPE; i++) {
        QPoint new_loc = f + MOVE[i];

        if (!isInRange(new_loc)
                || m_board->getColorAt(new_loc) != -1
                || m_current_route.count(new_loc) > 0)
            continue;

        m_current_route.push_back(new_loc);

        if (makeReachableBy(new_loc, t, depth - 1))
            return true;
        else
            m_current_route.pop_back();
    }

    return false;
}

bool FlowContextController::isOutOfTerminal(QPoint location)
{
    // check if it's out of terminal to avoid overflowing
    QPoint last_point = m_current_route.back();
    return m_board->getColorAt(last_point) == getCurrentColor()
            && m_current_route.size() > 1;
}


bool FlowContextController::isInRange(QPoint location)
{
    return location.x() >= 0
        && location.x() < m_board->getWidth()
        && location.y() >= 0
        && location.y() < m_board->getHeight();
}

/*
 * Setters
 */
void FlowContextController::setCurrentColor(int color)
{
    emit colorChanged(m_current_color = color);
}

void FlowContextController::setMoves(int moves)
{
    emit movesChanged(m_moves = moves);
}
