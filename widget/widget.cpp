#include "widget.h"
#include <QPainter>
#include <QPixmap>
#include "game/game.h"
#include <QThread>
#include "data.h"
#include <QDebug>
#include <QKeyEvent>

Widget::Widget(QWidget *parent) : QWidget(parent)
{

    this->setFixedSize(Data::instance()->getsize());
    this->setFocus();
//    QWidget::setFocusProxy(this);

    pixmap_ = new QPixmap(this->size());

    game_ = new Game(pixmap_);
    thread_ = new QThread(this);
    game_->moveToThread(thread_);

    connect(thread_,SIGNAL(started()),game_,SLOT(drawStartSlot()));
    connect(thread_,SIGNAL(finished()),game_,SLOT(deleteLater()));
    connect(game_,SIGNAL(finish()),this,SLOT(update()));
    //    connect(this,SIGNAL(drawFieldSignal()),game_,SLOT(drawFieldViewSlot())); //drawOneFrame drawGameSlot
    connect(this,SIGNAL(drawFieldSignal()),game_,SLOT(drawGameSlot()));

    thread_->start();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.drawPixmap(0,0,*pixmap_);
    painter.end();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<__FUNCTION__<<endl;

    switch (event->key()) {
    case Qt::Key_Up:
        game_->TurnTo(SD::Up);
        break;
    case Qt::Key_Down:
        game_->TurnTo(SD::Down);
        break;
    case Qt::Key_Left:
        game_->TurnTo(SD::Left);
        break;
    case Qt::Key_Right:
        game_->TurnTo(SD::Right);
        break;
    default:
        break;
    }


//    qDebug()<<__FUNCTION__<<endl;
}
Widget::~Widget()
{
    thread_->quit();
    thread_->wait();

    delete pixmap_;
    pixmap_ = nullptr;
}
