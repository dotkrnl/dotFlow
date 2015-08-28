#include "flowsolver.h"

FlowSolver::FlowSolver(FlowBoard *board, QObject *parent)
    : QObject(parent),
      m_board(board)
{
}

FlowContext FlowSolver::solve(void)
{
    m_pairs = m_board->getDotPairs();

    m_value.clear(); m_value.resize(m_board->getWidth());
    for (int i = 0; i < m_value.size(); i++) {
        m_value[i].resize(m_board->getHeight());
        for (int j = 0; j < m_value[i].size(); j++)
            m_value[i][j] = -1;
    }

    for (int i = 0; i < m_pairs.size(); i++)
        m_value[m_pairs[i].first.x()][m_pairs[i].first.y()]
                = m_value[m_pairs[i].second.x()][m_pairs[i].second.y()]
                = i;

    m_path.clear(); m_path.resize(m_pairs.size());

    m_path[0].push_back(m_pairs[0].first);
    bool solved = dfs(0, m_pairs[0].first);
    if (!solved) m_path[0].pop_back();

    FlowContext result(m_board);
    for (int i = 0; i < m_pairs.size(); i++)
        result.addRoute(i, m_path[i]);
    return result;
}

bool FlowSolver::dfs(int c, QPoint loc)
{
    if (loc == m_pairs[c].second) {
        if (c == m_pairs.size() - 1) {
            for (int i = 0; i < m_board->getWidth(); i++)
                for (int j = 0; j < m_board->getHeight(); j++)
                    if (m_value[i][j] == -1) return false;
            return true;
        } else {
            m_path[c+1].push_back(m_pairs[c+1].first);
            if (dfs(c+1, m_pairs[c+1].first)) return true;
            m_path[c+1].pop_back();
            return false;
        }
    }

    int firstX = m_pairs[c].second.x() - m_pairs[c].first.x()
            >= 0 ? 1 : -1;
    int firstY = m_pairs[c].second.y() - m_pairs[c].first.y()
            >= 0 ? 1 : -1;

    const int MOVE_TYPE = 4;
    const QPoint MOVE[MOVE_TYPE] = {
        QPoint(firstX, 0), QPoint(0, firstY),
        QPoint(-firstX, 0), QPoint(0, -firstY)
    };

    for (int i = 0; i < MOVE_TYPE; i++) {
        QPoint to = loc + MOVE[i];

        if (!isInRange(to)) continue;
        if (m_value[to.x()][to.y()] != -1
                && to != m_pairs[c].second) continue;

        m_path[c].push_back(to);
        if (to != m_pairs[c].second)
            m_value[to.x()][to.y()] = c;

        if (dfs(c, to)) return true;

        m_path[c].pop_back();
        if (to != m_pairs[c].second)
            m_value[to.x()][to.y()] = -1;
    }
    return false;
}

bool FlowSolver::isInRange(QPoint location)
{
    return location.x() >= 0
        && location.x() < m_board->getWidth()
        && location.y() >= 0
        && location.y() < m_board->getHeight();
}
