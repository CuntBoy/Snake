#include "mainwindow.h"
#include "widget/widget.h"
#include <QMenuBar>
#include "data.h"

void MainWindow::startSlot()
{
    if(Data::instance()->getStatus() != GT::Running)
        emit widget_->drawFieldSignal();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget_ = new Widget(this);

    this->setCentralWidget(widget_);

    //    w->resize(this->size());
    widget_->resize(Data::instance()->getsize());
    widget_->setFixedSize(Data::instance()->getsize());
    //this->setFixedSize(Data::instance()->getsize());
    initMenu();
}

void MainWindow::initMenu()
{
    QMenu * menu = this->menuBar()->addMenu("Game(&G)");
    menu->addAction("Start(&S)",this,SLOT(startSlot()));   // start Action
}


MainWindow::~MainWindow()
{

}

