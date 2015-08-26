#ifndef FLOWCOLOR_H
#define FLOWCOLOR_H

#include <QColor>

#define FLOW_BORDER     (QColor(0x55, 0x57, 0x59))
#define FLOW_BACKGROUND (QColor(0x40, 0x42, 0x44))

// TODO: use relative size
// should always be even number
#define FLOW_BORDER_SIZE     6

#define FLOW_DOT_RSIZE       0.6
#define FLOW_MOUSE_RSIZE     0.8
#define FLOW_LINE_RSIZE      0.35

static QColor CURRENT_DOT_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7)),
    (QColor(0x8A, 0xA7, 0xE3)),
    (QColor(0xA7, 0xE3, 0x8A)),
    (QColor(0xE3, 0xA7, 0x8A)),
};

static QColor CURRENT_LINE_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7)),
    (QColor(0x8A, 0xA7, 0xE3)),
    (QColor(0xA7, 0xE3, 0x8A)),
    (QColor(0xE3, 0xA7, 0x8A)),
};

static QColor CURRENT_CONTEXT_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7, 40)),
    (QColor(0x8A, 0xA7, 0xE3, 40)),
    (QColor(0xA7, 0xE3, 0x8A, 40)),
    (QColor(0xE3, 0xA7, 0x8A, 40)),
};

static QColor CURRENT_MOUSE_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7, 50)),
    (QColor(0x8A, 0xA7, 0xE3, 50)),
    (QColor(0xA7, 0xE3, 0x8A, 50)),
    (QColor(0xE3, 0xA7, 0x8A, 50)),
};


static QColor MOUSE_DEFAULT_COLOR = QColor(0x55, 0x57, 0x59, 127);

#endif // FLOWCOLOR_H
