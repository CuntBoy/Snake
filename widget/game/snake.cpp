#include "snake.h"
#include "item.h"
#include "data.h"
#include <QPixmap>
#include <QPainter>
#include <QTransform>

Snake::Snake()
{
    init();
    pixmap_  = new QPixmap(Data::instance()->getsize()) ;
    pixmap_->fill(QColor("#00000000"));
    //    pixmap_->fill(QColor(Qt::white));
    pixhead_ = new QPixmap(":pic/pic/head.jpg") ;
    pixbody_ = new QPixmap(":pic/pic/body.png") ;
    pixtail_ = new QPixmap(":pic/pic/tial.png") ;
    *pixhead_ = pixhead_->scaled(Data::instance()->cellSize(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    *pixbody_ = pixbody_->scaled(Data::instance()->cellSize(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    *pixtail_ = pixtail_->scaled(Data::instance()->cellSize(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}


void Snake::init()
{
    int cellsize = Data::instance()->getcellsize();
    SnakeItem  headItem(QPoint(2*cellsize,Data::instance()->getrow()/2*cellsize),IType::SnakeHead);
    list_.push_back(headItem);
    SnakeItem  bodyItem(QPoint(cellsize,Data::instance()->getrow()/2*cellsize),IType::SnakeBody);
    list_.push_back(bodyItem);
    SnakeItem  tialItem(QPoint(0,Data::instance()->getrow()/2*cellsize),IType::SnakeTail);
    list_.push_back(tialItem);

}

// 旋转图片
QPixmap Snake::rotate(QPixmap * pixmap,SD::SnakeDirection direct)
{
    QTransform transform;
    transform.rotate(static_cast<int>(direct)*90);

    //    switch (direct) {
    //    case SD::Down:
    //        transform.rotate(-90);
    //        break;
    //    case SD::Up:
    //        transform.rotate(90);
    //        break;
    //    case SD::Left:
    //        transform.rotate(180);
    //        break;
    //    case SD::Right:
    //        break;
    //    }
    return pixmap->transformed(transform);

}

QPixmap * Snake::draw()
{
    QPainter painter;
    painter.begin(pixmap_);
    foreach (SnakeItem item, list_)
    {
        switch(item.gettype())
        {
        case IType::SnakeHead:
            //            painter.drawPixmap(item.getpos(),*(pixhead_));
            painter.drawPixmap(item.getpos(),rotate(pixhead_,item.getDirection()));
            break;
        case IType::SnakeBody:
            painter.drawPixmap(item.getpos(),rotate(pixbody_,item.getDirection()));
            break;
        case IType::SnakeTail:
            painter.drawPixmap(item.getpos(),rotate(pixtail_,item.getDirection()));
            break;
        }
    }

    painter.end();
    return pixmap_;

}

// 蛇移动
// 舌头的范围 0-cellsize * column
void Snake::move()
{
    QPoint nextpos = nextHead();
    if(nextpos.x() < 0
            || nextpos.x()>= Data::instance()->getcellsize()*Data::instance()->getcolumn()
            || nextpos.y()<0
            || nextpos.y() >= Data::instance()->getcellsize()*Data::instance()->getrow())
    {
        qDebug()<<"game over"<<endl;
        Data::instance()->setStatus(GT::Over);
        return;
    }
    for(int i = list_.length()-1; i > 0; i--)
    {
        list_[i].setpos(list_[i-1].getpos());
        list_[i].setDirection(list_[i-1].getDirection());
    }
    list_[0].setpos(nextpos);


}

void Snake::TurnTo(SD::SnakeDirection direct)
{
    if(list_[0].getDirection() +direct % 2 != 0)
    {
        list_[0].setDirection(direct);
    }
//    switch (direct) {
//    case SD::Up:
//        if(list_[0].getDirection() != SD::Down)
//        {
//            list_[0].setDirection(direct);
//        }
//        break;
//    case SD::Down:
//        if(list_[0].getDirection() != SD::Up)
//        {
//            list_[0].setDirection(direct);
//        }
//        break;
//    case SD::Left:
//        if(list_[0].getDirection() != SD::Right)
//        {
//            list_[0].setDirection(direct);
//        }
//        break;
//    case SD::Right:
//        if(list_[0].getDirection() != SD::Left)
//        {
//            list_[0].setDirection(direct);
//        }
//        break;
//    default:
//        break;
//    }
//    list_[0].setDirection(direct);
}

// 获取下一个蛇头的位置
QPoint Snake::nextHead()
{
    QPoint nextPos;
    int cellWidth = Data::instance()->getcellsize();

    switch (list_[0].getDirection())
    {
    case SD::Up:
        nextPos = QPoint(list_[0].getpos().x(),list_[0].getpos().y()-cellWidth);
        break;
    case SD::Right:
        nextPos = list_[0].getpos() + QPoint(cellWidth,0);
        break;
    case SD::Down:
        nextPos = QPoint(list_[0].getpos().x(),list_[0].getpos().y()+cellWidth);
        break;
    case SD::Left:
        nextPos = QPoint(list_[0].getpos().x()-cellWidth,list_[0].getpos().y());
        break;
    default:
        break;
    }
    return nextPos;
}

//添加身体 长长
void Snake::addItem()
{
    SnakeItem newHead = list_[0];
    newHead.setpos(nextHead());
    list_[0].settype(IType::SnakeBody);
    list_.insert(0,newHead);
}

Snake:: ~Snake()
{
    delete pixmap_ ;
    delete pixhead_;
    delete pixbody_;
    delete pixtail_;

    pixmap_  = nullptr;
    pixhead_ = nullptr;
    pixbody_ = nullptr;
    pixtail_ = nullptr;

}

