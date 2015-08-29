#ifndef FLOWBOARDCONTROLLER_H
#define FLOWBOARDCONTROLLER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QDirIterator>
#include <QSettings>
#include <QFileDialog>
#include <QFileInfo>

#include "globalconstant.h"
#include "flowboard.h"

class FlowBoardController : public QObject
{
    Q_OBJECT

public:
    explicit FlowBoardController(QObject *parent = 0);

    int current(void) { return m_current; }
    int total(void) { return m_files.size(); }

    FlowBoard *getBoard(void) { return m_board; }

    int getBest(void);
    int getBest(int level);
    bool getPerfect(void);
    bool getPerfect(int level);

protected:
    QVector<QString> m_files;
    FlowBoard *m_board;
    QSettings *m_settings;

    int m_current;
    QString m_current_file;

    void setBest(int level, int value, bool perfect);

signals:
    void gameInitialized(void);

    void bestChanged(int level, int value, bool perfect);
    void levelChanged(int level);

public slots:
    void previous(void);
    void next(void);
    void restart(void);
    void random(void);
    void select(int level);

    void initGame(void);
    void updateBest(int best, bool perfect);
    void loadExternal(void);

private slots:
    void loadBoard(void);

};

#endif // FLOWBOARDCONTROLLER_H
