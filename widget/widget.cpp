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
    pixmap_ = new QPixmap(this->size());
    game_ = new Game(pixmap_);
    thread_ = new QThread(this);
    game_->moveToThread(thread_);

    connect(thread_,SIGNAL(started()),game_,SLOT(drawStartSlot()));
    connect(this,&Widget::drawStartView,game_,&Game::drawStartSlot);

    connect(thread_,SIGNAL(finished()),game_,SLOT(deleteLater()));
    connect(game_,SIGNAL(finish()),this,SLOT(update()));
    connect(this,SIGNAL(drawFieldSignal()),game_,SLOT(drawFieldViewSlot())); //drawOneFrame drawGameSlot
    connect(this,SIGNAL(drawFieldSignal()),game_,SLOT(drawGameSlot()));

    connect(this,SIGNAL(reinitlizedSnak()),game_,SLOT(OnUpdateSnake()));


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
    case Qt::Key_Space:
        if(Data::instance()->getStatus() == GT::Running)
        {
            Data::instance()->setStatus(GT::Pause);
        }
        else if(Data::instance()->getStatus() == GT::Over)
        {
            Data::instance()->setStatus(GT::Start);
            //emit drawFieldSignal();
            emit reinitlizedSnak();
            emit drawStartView();
        }
        else
        {
            if(Data::instance()->getStatus() == GT::Start)
            {
                emit reinitlizedSnak();
            }

            Data::instance()->setStatus(GT::Running);
            emit drawFieldSignal();
        }

    default:
        break;
    }

}

Widget::~Widget()
{
    // 等待线程退出 -- 然后才调用删除
    thread_->quit();
    thread_->wait();

    delete pixmap_;
    pixmap_ = nullptr;
}
