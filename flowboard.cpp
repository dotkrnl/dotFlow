#include "flowboard.h"

FlowBoard::FlowBoard(QObject *parent)
    : QObject(parent)
{
}

int FlowBoard::getWidth(void)
{
    return m_width;
}

int FlowBoard::getHeight(void)
{
    return m_height;
}

DotPairVector FlowBoard::getDotPairs(void)
{
    return m_pairs;
}

void FlowBoard::setHeight(int height)
{
    m_height = height;
}

void FlowBoard::setWidth(int width)
{
    m_width = width;
}

void FlowBoard::addDotPair(DotPair pair)
{
    m_pairs.append(pair);
}

void FlowBoard::loadFrom(QFile *boardDesc)
{
    QTextStream input(boardDesc);

    int height, width;
    input >> width >> height;
    input.skipWhiteSpace();
    setHeight(height);
    setWidth(width);

    while (!input.atEnd()) {
        int x1, y1, x2, y2;
        input >> x1 >> y1 >> x2 >> y2;
        input.skipWhiteSpace();
        addDotPair(DotPair(
            QPoint(x1, y1), QPoint(x2, y2)
        ));
    }

    emit boardLoaded();
}
