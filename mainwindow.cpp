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
    this->setWindowIcon(
                QIcon(
                    QPixmap(":pic/pic/window_title.png").scaled(QSize(16,16),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    // 创建显示的窗口
    widget_ = new Widget(this);

    // 设置中心窗口
    this->setCentralWidget(widget_);

    // 设置中心窗口的显示大小
    widget_->resize(Data::instance()->getsize());
    widget_->setFixedSize(Data::instance()->getsize());
    //this->setFixedSize(Data::instance()->getsize());

    // 固定大小
    // this->setFixedSize(this->size());
    //this->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    // 初始化菜单
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

