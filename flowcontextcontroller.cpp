#include "flowcontextcontroller.h"

FlowContextController::FlowContextController(FlowBoard *mother, QObject *parent)
    : QObject(parent),
      m_stable(new FlowContext(mother, this)),
      m_beta(new FlowContext(mother, this)),
      m_board(mother)
{
    connect(m_board, SIGNAL(boardLoaded(int)),
            this, SLOT(initFlowContext(int)));
}

FlowContext *FlowContextController::getDisplayContext(void) {
    return m_beta;
}

void FlowContextController::initFlowContext(int color_count)
{
    // TODO: clear undo stack if implemented
}

void FlowContextController::startRoute(QPoint location)
{
    if (!isInRange(location)) return;

    int dot_color = m_board->getColorAt(location);
    int context_color = m_beta->getColorAt(location);
    int color = dot_color != -1 ?
                dot_color : context_color;

    m_current_color = color;
    emit colorChanged(m_current_color);

    if (m_current_color == -1)
        // on the board
        return;

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
    if (m_current_color == -1) return;
    if (!isInRange(location)) return;

    // don't link to terminal dots of other colors
    if (isTerminalDotsOfOthers(location)) return;

    truncateCurrentRoute(location);
    if (m_current_route.size() == 0 ||
        // first time or over-truncated?
            // or satisfy the conditions
            (isNearTheEndOfRoute(location)
             && !isOutOfTerminal(location)))
        m_current_route.append(location);

    m_stable->cloneTo(*m_beta, false); // update later
    m_beta->addRoute(m_current_color, m_current_route);
    // i.e. addRoute here will update view
}

void FlowContextController::endRoute(void)
{
    m_current_color = -1;
    m_beta->cloneTo(*m_stable);
}

/*
 * Utility functions
 */

bool FlowContextController::isTerminalDotsOfOthers(QPoint location)
{
    int dot_color = m_board->getColorAt(location);
    return dot_color != -1 && dot_color != m_current_color;
}

void FlowContextController::truncateCurrentRoute(QPoint terminal)
{
    for (int i = 0; i < m_current_route.size(); i++) {
        if (terminal == m_current_route[i])
            m_current_route.resize(i);
    }
}

bool FlowContextController::isNearTheEndOfRoute(QPoint location)
{
    static const int MOVE_TYPE = 4;
    static const QPoint MOVE[4] = {
        QPoint(1, 0), QPoint(-1, 0),
        QPoint(0, 1), QPoint(0, -1),
    };

    // check if it's near the last point of route to avoid jumping
    QPoint last_point = m_current_route[m_current_route.size() - 1];
    for (int i = 0; i < MOVE_TYPE; i++)
        if (location == last_point + MOVE[i])
            return true;

    return false;
}

bool FlowContextController::isOutOfTerminal(QPoint location)
{
    // check if it's out of terminal to avoid overflowing
    QPoint last_point = m_current_route[m_current_route.size() - 1];
    return m_board->getColorAt(last_point) == m_current_color
            && m_current_route.size() > 1;
}


bool FlowContextController::isInRange(QPoint location)
{
    return location.x() >= 0
        && location.x() < m_board->getWidth()
        && location.y() >= 0
        && location.y() < m_board->getHeight();
}
