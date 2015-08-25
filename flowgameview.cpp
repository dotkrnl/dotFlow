#include "flowgameview.h"

FlowGameView::FlowGameView(QWidget *parent)
    : QWidget(parent),
      m_board(new FlowBoard(this))
{
    // TODO: should be managed by mainwindow
    QFile file("/Users/dotkrnl/Workspace/qt/dotflow/testdata");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    m_board->loadFrom(&file);
    connect(m_board, SIGNAL(boardLoaded(int)),
            this, SLOT(boardChanged()));
}

void FlowGameView::recalculateCommonSize(void)
{
    int raw_height = this->height();
    int raw_width  = this->width();

    m_line = m_board->getHeight();
    m_col  = m_board->getWidth();

    m_ppl = (raw_height - FLOW_BORDER_SIZE) / m_line;
    m_ppc = (raw_width  - FLOW_BORDER_SIZE) / m_col;

    m_wzero = m_hzero = FLOW_BORDER_SIZE / 2 + 1;
    m_height = m_ppl * m_line;
    m_width = m_ppc * m_col;
}

void FlowGameView::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    this->recalculateCommonSize();
}

void FlowGameView::boardChanged(void)
{
    this->update();
    this->recalculateCommonSize();
}

void FlowGameView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(
        QPainter::Antialiasing
      | QPainter::TextAntialiasing);
    painter.translate(m_hzero, m_hzero);

    drawBoard(painter);
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
        painter.setPen(QPen(CURRENT_THEME[i]));
        painter.setBrush(QBrush(CURRENT_THEME[i]));
        drawDot(painter, dot_pairs[i].first);
        drawDot(painter, dot_pairs[i].second);
    }
}

void FlowGameView::drawDot(QPainter &painter, QPoint dot)
{
    int dot_diameter = qMin(m_ppl, m_ppc) * FLOW_DOT_SIZE;
    int x = dot.x(), y = dot.y();
    int center_x =  x * m_ppc + m_ppc / 2;
    int center_y =  y * m_ppl + m_ppl / 2;
    painter.drawEllipse(center_x - dot_diameter / 2,
                        center_y - dot_diameter / 2,
                        dot_diameter, dot_diameter);
}

void FlowGameView::drawMouse(QPainter &painter)
{
    if (!m_pressed) return;
    painter.setPen(QPen(MOUSE_COLOR));
    painter.setBrush(QBrush(MOUSE_COLOR));
    int dot_diameter = qMin(m_ppl, m_ppc) * FLOW_MOUSE_SIZE;
    painter.drawEllipse(m_mouse_pos.x() - dot_diameter / 2,
                        m_mouse_pos.y() - dot_diameter / 2,
                        dot_diameter, dot_diameter);
}

void FlowGameView::mousePressEvent(QMouseEvent *event)
{
    m_pressed = true;
    m_mouse_pos = event->pos() - QPoint(m_wzero, m_hzero);
    this->update();
}

void FlowGameView::mouseMoveEvent(QMouseEvent *event)
{
    m_mouse_pos = event->pos() - QPoint(m_wzero, m_hzero);
    this->update();
}

void FlowGameView::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    this->update();
}
