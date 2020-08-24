#include "mainwindow.h"
#include "widget/widget.h"
#include <QMenuBar>
#include "data.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget_ = new Widget;
    //    w->resize(this->size());
    this->setCentralWidget(widget_);
//    widget_->resize(Data::instance()->getsize());
//    widget_->setFixedSize(Data::instance()->getsize());
//    this->setFixedSize(Data::instance()->getsize());
    initMenu();
}

void MainWindow::initMenu()
{
    QMenu * menu = this->menuBar()->addMenu("Game(&G)");
    menu->addAction("Start(&S)",widget_,SIGNAL(drawFieldSignal()));
}


MainWindow::~MainWindow()
{

}

