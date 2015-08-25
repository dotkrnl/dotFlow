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
    int dot_color = m_board->getColorAt(location);
    int context_color = m_beta->getColorAt(location);
    int color = dot_color != -1 ? dot_color : context_color;

    m_current_color = color;
    if (context_color == -1) m_current_route.resize(0);
    else m_current_route = m_beta->getRouteOf(color);

    newRoutePoint(location);
}

void FlowContextController::newRoutePoint(QPoint location)
{
    int dot_color = m_board->getColorAt(location);
    if (dot_color != m_current_color) return;

    for (int i = 1; i < m_current_route.size(); i++) {
        if (location == m_current_route[i])
            m_current_route.resize(i);
    }

    static const int MOVE_TYPE = 4;
    static const QPoint MOVE[4] = {
        QPoint(1, 0), QPoint(-1, 0),
        QPoint(0, 1), QPoint(0, -1),
    };
    QPoint last_point = m_current_route[m_current_route.size() - 1];
    for (int i = 0; i < MOVE_TYPE; i++) {
        if (location == last_point + MOVE[i]) // near
            m_current_route.append(location);
    }

    m_stable->cloneTo(*m_beta, false); // update later
    m_beta->addRoute(m_current_color, m_current_route); // i.e. here
}

void FlowContextController::endRoute(void)
{
    m_beta->cloneTo(*m_stable);
}
