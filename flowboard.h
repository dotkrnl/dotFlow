#ifndef FLOWBOARD_H
#define FLOWBOARD_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QPair>
#include <QPoint>

typedef QPair<QPoint, QPoint> DotPair;
typedef QVector<DotPair> DotPairVector;

/*
 * A class to store layout of the board
 */
class FlowBoard : public QObject
{
    Q_OBJECT

public:
    explicit FlowBoard(QObject *parent = 0);

    int getHeight(void);
    int getWidth(void);

    DotPairVector getDotPairs(void);
    int getDotPairsCount(void);
    int getColorAt(QPoint location);

    /*
     * Load gameboard from description file:
     * 4 4     // height width
     * 1 1 4 4 // first pair
     * ... ... // more pairs
     */
    void loadFrom(QFile *boardDesc);

private:
    int m_height, m_width;
    DotPairVector m_pairs;

    void setHeight(int height);
    void setWidth(int width);
    void addDotPair(DotPair pair);

signals:
    /*
     * Emit after board information is ready
     * when board is loaded or reloaded
     */
    void boardLoaded(int dot_pair_count);

public slots:

};

#endif // FLOWBOARD_H
