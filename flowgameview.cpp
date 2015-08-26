#include "flowgameview.h"

FlowGameView::FlowGameView(QWidget *parent)
    : QWidget(parent),
      m_board(new FlowBoard(this)), // TODO: should be an input
      m_mouse_color(-1)
{
    // TODO: should be managed by mainwindow
    QFile file("/Users/dotkrnl/Workspace/qt/dotflow/testdata");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    m_board->loadFrom(&file);
    connect(m_board, SIGNAL(boardLoaded(int)),
            this, SLOT(boardChanged()));

    // TODO: should be managed by mainwindow
    m_controller = new FlowContextController(m_board, this);
    connect(m_controller, SIGNAL(colorChanged(int)),
            this, SLOT(mouseColorChanged(int)));
    m_context = m_controller->getDisplayContext();
    connect(m_context, SIGNAL(contextUpdated()),
            this, SLOT(contextChanged()));
}

QPoint FlowGameView::decodeLocation(QPoint mouse)
{
    int x = mouse.x() / m_ppc;
    int y = mouse.y() / m_ppl;
    return QPoint(x, y);
}

QPoint FlowGameView::encodeLocation(QPoint location)
{
    int center_x =  location.x() * m_ppc + m_ppc / 2;
    int center_y =  location.y() * m_ppl + m_ppl / 2;
    return QPoint(center_x, center_y);
}

void FlowGameView::recalculateCommonSize(void)
{
    int raw_width  = this->width();
    int raw_height = this->height();

    m_col  = m_board->getWidth();
    m_line = m_board->getHeight();

    m_ppc = (raw_width  - FLOW_BORDER_SIZE) / m_col;
    m_ppl = (raw_height - FLOW_BORDER_SIZE) / m_line;
    if (m_ppc & 1) m_ppc--; // even number fix
    if (m_ppl & 1) m_ppl--; // even number fix

    m_wzero = m_hzero = FLOW_BORDER_SIZE / 2 + 1;
    m_width = m_ppc * m_col;
    m_height = m_ppl * m_line;

    m_relative_size = qMin(m_ppl, m_ppc);
}

void FlowGameView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    this->recalculateCommonSize();
}

void FlowGameView::boardChanged(void)
{
    this->recalculateCommonSize();
    this->update();
}

void FlowGameView::contextChanged(void)
{
    this->update();
}

void FlowGameView::mouseColorChanged(int color)
{
    m_mouse_color = color;
}

void FlowGameView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(
        QPainter::Antialiasing
      | QPainter::TextAntialiasing);
    painter.translate(m_hzero, m_hzero);

    drawContextBoard(painter);
    drawBoard(painter);
    drawContext(painter);
    drawDots(painter);
    drawMouse(painter);
}

void FlowGameView::drawBoard(QPainter &painter)
{
    QPen boardPen(FLOW_BORDER);
    boardPen.setWidth(FLOW_BORDER_SIZE);
    painter.setPen(boardPen);

    for (int i = 0; i <= m_line; i++) {
        int line_loc = i * m_ppl;
        painter.drawLine(0,       line_loc,
                         m_width, line_loc);
    }
    for (int i = 0; i <= m_col; i++) {
        int col_loc = i * m_ppc;
        painter.drawLine(col_loc, 0,
                         col_loc, m_height);
    }
}

void FlowGameView::drawDots(QPainter &painter)
{
    DotPairVector dot_pairs = m_board->getDotPairs();
    for (int i = 0; i < dot_pairs.size(); i++) {
        drawDot(painter, dot_pairs[i].first, i);
        drawDot(painter, dot_pairs[i].second, i);
    }
}

void FlowGameView::drawDot(QPainter &painter,
                           QPoint dot, int color)
{
    QPoint center = encodeLocation(dot);
    int dot_diameter = m_relative_size * FLOW_DOT_RSIZE;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(CURRENT_DOT_THEME[color]));

    drawRound(painter, center, dot_diameter);
}

void FlowGameView::drawMouse(QPainter &painter)
{
    // TODO: maybe should be a widget
    if (!m_pressed) return;
    painter.setPen(Qt::NoPen);
    if (m_mouse_color == -1) {
        painter.setBrush(QBrush(MOUSE_DEFAULT_COLOR));
    } else {
        painter.setBrush(QBrush(CURRENT_MOUSE_THEME[m_mouse_color]));
    }
    int dot_diameter = m_relative_size * FLOW_MOUSE_RSIZE;
    drawRound(painter, m_mouse_pos, dot_diameter);
}

void FlowGameView::drawContext(QPainter &painter)
{
    for (int c = 0; c < m_board->getColorCount(); c++) {
        PointSeries route = m_context->getRouteOf(c);
        for (int i = 1; i < route.size(); i++)
            drawRoundedLine(painter, route[i-1], route[i], c);
    }
}

void FlowGameView::drawContextBoard(QPainter &painter)
{
    for (int c = 0; c < m_board->getColorCount(); c++) {
        PointSeries route = m_context->getRouteOf(c);
        for (int i = 1; i < route.size(); i++) {
            QPoint from = encodeLocation(route[i-1]);
            QPoint to   = encodeLocation(route[i]);
            QPen boardPen(CURRENT_CONTEXT_THEME[c]);
            boardPen.setWidth(m_relative_size);
            painter.setPen(boardPen);
            painter.drawLine(from, to);
        }
    }
}

void FlowGameView::drawRoundedLine(QPainter &painter,
                                   QPoint f, QPoint t, int color)
{
    QPoint from = encodeLocation(f);
    QPoint to   = encodeLocation(t);

    int line_width = m_relative_size * FLOW_LINE_RSIZE;
    if (line_width & 1) line_width++; // even number fix

    int line_length = std::sqrt(
        double(QPoint::dotProduct(to - from, to - from)));
    QPoint unit = (to - from) / line_length;

    // draw line
    QPen boardPen(CURRENT_LINE_THEME[color]);
    boardPen.setWidth(line_width);
    painter.setPen(boardPen);
    painter.drawLine(from + unit * line_width / 2,
                     to   - unit * line_width / 2);

    // draw round
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(CURRENT_LINE_THEME[color]));
    drawRound(painter, from, line_width);
    drawRound(painter, to  , line_width);
}

void FlowGameView::drawRound(QPainter &painter,
                             QPoint center, int diameter)
{
    if (diameter & 1) diameter++; // even number fix
    painter.drawEllipse(
                center.x() - diameter / 2,
                center.y() - diameter / 2,
                diameter, diameter);
}


void FlowGameView::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_mouse_pos = event->pos() - QPoint(m_wzero, m_hzero);
    m_controller->startRoute(decodeLocation(m_mouse_pos));
    this->update();
}

void FlowGameView::mouseMoveEvent(QMouseEvent *event)
{
    m_mouse_pos = event->pos() - QPoint(m_wzero, m_hzero);
    m_controller->newRoutePoint(decodeLocation(m_mouse_pos));
    this->update();
}

void FlowGameView::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    m_controller->endRoute();
    this->update();
}
