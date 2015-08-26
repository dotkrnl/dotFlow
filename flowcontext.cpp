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

void FlowContext::initFlowContext(int color_count)
{
    m_context.resize(0);
    m_context.resize(color_count);
    emit contextUpdated();
}

int FlowContext::getColorAt(QPoint location)
{
    for (int c = 0; c < m_context.size(); c++) {
        for (int i = 0; i < m_context[c].size(); i++)
            if (location == m_context[c][i])
                return c;
    }
    return -1;
}

PointSeries FlowContext::getRouteOf(int color)
{
    return m_context[color];
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

void FlowContext::cloneTo(FlowContext &dest, bool update)
{
    dest.m_context = m_context;
    if (update) emit dest.contextUpdated();
}

void FlowContext::calculateRatio(void)
{
    int total = m_board->getWidth() *
                m_board->getHeight();

    int done = 0;
    for (int c = 0; c < m_context.size(); c++)
        done += m_context[c].size();

    emit contextRatioChanged(double(done) / total);
}
