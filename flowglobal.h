#ifndef FLOWCOLOR_H
#define FLOWCOLOR_H

#include <QColor>

#define FLOW_BORDER     (QColor(0x55, 0x57, 0x59))
#define FLOW_BACKGROUND (QColor(0x40, 0x42, 0x44))

#define FLOW_BORDER_SIZE    5
#define FLOW_DOT_SIZE       0.6
#define FLOW_MOUSE_SIZE     0.5

static QColor CURRENT_THEME[] = {
    (QColor(0xE3, 0x8A, 0xA7)),
    (QColor(0x8A, 0xA7, 0xE3)),
    (QColor(0xA7, 0xE3, 0x8A)),
};

static QColor MOUSE_COLOR = QColor(0x55, 0x57, 0x59, 127);

#endif // FLOWCOLOR_H
