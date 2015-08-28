#include "flowcontext.h"

FlowContext::FlowContext(FlowBoard *mother, QObject *parent)
    : QObject(parent),
      m_board(mother)
{
    connect(m_board, SIGNAL(boardLoaded(int)),
            this, SLOT(initFlowContext(int)));
    connect(this, SIGNAL(contextUpdated()),
            this, SLOT(calculateRatio()));
    initFlowContext(m_board->getColorCount());
}

FlowContext::FlowContext(const FlowContext &o)
{
    o.cloneTo(*this);
}

void FlowContext::initFlowContext(int color_count)
{
    m_context.resize(0);
    m_context.resize(color_count);
    emit contextUpdated();
}

int FlowContext::getColorAt(QPoint location) const
{
    for (int c = 0; c < m_context.size(); c++) {
        for (int i = 0; i < m_context[c].size(); i++)
            if (location == m_context[c][i])
                return c;
    }
    return -1;
}

PointSeries FlowContext::getRouteOf(int color) const
{
    return m_context[color];
}

bool FlowContext::isTruncatedComparedTo(const FlowContext &ot) const
{
    for (int c = 0; c < ot.m_context.size(); c++) {
        if (!(ot.m_context[c].size() > 1)) continue;

        QPoint o_tail = ot.m_context[c].back();
        int o_color = ot.m_board->getColorAt(o_tail);
        if (!(o_color == c)) continue;

        if (m_context[c].size() <= 1) return true;

        QPoint m_tail = m_context[c].back();
        int m_color = m_board->getColorAt(m_tail);
        if (m_color != c) return true;
    }
    return false;
}

void FlowContext::addRoute(int color, PointSeries route)
{
    for (int d = 0; d < route.size(); d++) {
        QPoint dot = route[d];
        for (int c = 0; c < m_context.size(); c++) {
            for (int i = 0; i < m_context[c].size(); i++)
                if (dot == m_context[c][i])
                    m_context[c].resize(i);
            // truncate paths of all colors with intersection
        }
    }
    m_context[color] = route;
    emit contextUpdated();
}

void FlowContext::cloneTo(FlowContext &dest, bool update) const
{
    dest.m_context = m_context;
    if (update) emit dest.contextUpdated();
}

double FlowContext::getRatio(void) const
{
    int total = m_board->getWidth() *
                m_board->getHeight();

    int done = 0;
    for (int c = 0; c < m_context.size(); c++)
        done += m_context[c].size();

    return double(done) / total;
}

void FlowContext::calculateRatio(void)
{
    emit contextRatioChanged(getRatio());
}
