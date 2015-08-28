#ifndef FLOWCOLOR_H
#define FLOWCOLOR_H

#include <QColor>

#define GAMEINFO_DIR    ":/gameinfo/res/games"

// TODO: use relative size
// should always be even number
#define FLOW_BORDER_SIZE     6

#define FLOW_DOT_RSIZE       0.6
#define FLOW_MOUSE_RSIZE     0.8
#define FLOW_LINE_RSIZE      0.35

#define MAX_FIND_ROUTE       5

static QColor CURRENT_DOT_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7)),
    (QColor(0x7E, 0x9A, 0xF3)),
    (QColor(0xA7, 0xE3, 0x8A)),
    (QColor(0xE3, 0xA7, 0x8A)),
    (QColor(0xA7, 0x8A, 0xE3)),
    (QColor(0x36, 0xE6, 0xE9)),
    (QColor(0xCB, 0xCD, 0x00)),
    (QColor(0xBA, 0xBA, 0xBA)),
};

static QColor CURRENT_LINE_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7)),
    (QColor(0x7E, 0x9A, 0xF3)),
    (QColor(0xA7, 0xE3, 0x8A)),
    (QColor(0xE3, 0xA7, 0x8A)),
    (QColor(0xA7, 0x8A, 0xE3)),
    (QColor(0x36, 0xE6, 0xE9)),
    (QColor(0xCB, 0xCD, 0x00)),
    (QColor(0xBA, 0xBA, 0xBA)),
};

static QColor CURRENT_CONTEXT_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7, 40)),
    (QColor(0x7E, 0x9A, 0xF3, 40)),
    (QColor(0xA7, 0xE3, 0x8A, 40)),
    (QColor(0xE3, 0xA7, 0x8A, 40)),
    (QColor(0xA7, 0x8A, 0xE3, 40)),
    (QColor(0x36, 0xE6, 0xE9, 40)),
    (QColor(0xCB, 0xCD, 0x00, 40)),
    (QColor(0xBA, 0xBA, 0xBA, 40)),
};

static QColor CURRENT_MOUSE_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7, 50)),
    (QColor(0x7E, 0x9A, 0xF3, 50)),
    (QColor(0xA7, 0xE3, 0x8A, 50)),
    (QColor(0xE3, 0xA7, 0x8A, 50)),
    (QColor(0xA7, 0x8A, 0xE3, 50)),
    (QColor(0x36, 0xE6, 0xE9, 50)),
    (QColor(0xCB, 0xCD, 0x00, 50)),
    (QColor(0xBA, 0xBA, 0xBA, 50)),
};

static QColor FLOW_BORDER =
        QColor(0x55, 0x57, 0x59);

static QColor FLOW_BACKGROUND =
        QColor(0x40, 0x42, 0x44);

static QColor MOUSE_DEFAULT_COLOR =
        QColor(0x55, 0x57, 0x59, 127);

#endif // FLOWCOLOR_H