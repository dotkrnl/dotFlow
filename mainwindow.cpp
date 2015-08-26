#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCursor(QCursor(Qt::CrossCursor));

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, FLOW_BACKGROUND);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}
