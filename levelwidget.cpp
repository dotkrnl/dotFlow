#include "levelwidget.h"
#include "ui_levelwidget.h"

LevelWidget::LevelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelWidget),
    m_select_mapper(NULL)
{
    ui->setupUi(this);

    ui->listWidget->viewport()->setAutoFillBackground(false);
    ui->listWidget->verticalScrollBar()
        ->setStyleSheet("QScrollBar:vertical {"
                        "border: none;"
                        "width: 0px;"
        "}");

    connect(ui->hideButton, SIGNAL(clicked(bool)),
            this, SIGNAL(hideClicked()));
    connect(this, SIGNAL(hideClicked()),
            this, SLOT(hide()));

    connect(ui->restartButton, SIGNAL(clicked(bool)),
            this, SIGNAL(restartClicked()));
    connect(ui->randomButton, SIGNAL(clicked(bool)),
            this, SIGNAL(randomClicked()));
    connect(ui->loadButton, SIGNAL(clicked(bool)),
            this, SIGNAL(loadClicked()));
    connect(ui->resetButton, SIGNAL(clicked(bool)),
            this, SIGNAL(resetClicked()));

}

LevelWidget::~LevelWidget()
{
    delete ui;
}

void LevelWidget::useBoardController(FlowBoardController *b)
{
    m_board = b;

    if (m_select_mapper) delete m_select_mapper;
    m_select_mapper = new QSignalMapper(this);

    for (int i = 0; i < m_board->total(); i++) {
        LevelItemWidget *item =
            new LevelItemWidget(i, this);

        item->setBest(i, m_board->getBest(i),
                         m_board->getPerfect(i));
        connect(m_board, SIGNAL(bestChanged(int,int,bool)),
                item, SLOT(setBest(int,int,bool)));

        item->setLevel(m_board->current());
        connect(m_board, SIGNAL(levelChanged(int)),
                item, SLOT(setLevel(int)));

        connect(item, SIGNAL(selected()),
                m_select_mapper, SLOT(map()));
        m_select_mapper->setMapping(item, i);

        QListWidgetItem *l_item = new QListWidgetItem();
        l_item->setSizeHint(QSize(0, 80));
        ui->listWidget->addItem(l_item);
        ui->listWidget->setItemWidget(l_item, item);
    }

    connect(m_select_mapper, SIGNAL(mapped(int)),
            this, SIGNAL(selected(int)));
}

void LevelWidget::showEvent(QShowEvent *event)
{
    QListWidgetItem *item =
            ui->listWidget->item(m_board->current());
    ui->listWidget->scrollToItem(item);
}
