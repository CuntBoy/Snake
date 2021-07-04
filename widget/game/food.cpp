#include "food.h"
#include <time.h>
#include "data.h"
#include <QPainter>

Food::Food()
{
    pixmap_ = new  QPixmap(Data::instance()->getsize());
    pixmap_->fill(QColor("#00000000"));
    foodpix_ = new QPixmap(":pic/pic/food.png");

    *foodpix_ = foodpix_->scaled(Data::instance()->getcellsize(),Data::instance()->getcellsize(),
                                 Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->update();
}

void Food::update()
{
    srand(time(NULL));
    int row = rand()%Data::instance()->getrow();
    int column = rand()%Data::instance()->getcolumn();
    this->setpos(QPoint(column*Data::instance()->getcellsize(),row*Data::instance()->getcellsize()));
}

QPixmap * Food::draw()
{
    pixmap_->fill(QColor("#00000000"));
    QPainter painter;
    painter.begin(pixmap_);
    painter.drawPixmap(this->getpos(),*foodpix_);
    painter.end();
    return pixmap_;
}

void Food::update(const QList<QPoint> & list)
{
    srand(time(NULL));
    int index = rand() % list.length();
    //list.removeOne(this->getpos());
    this->setpos(list[index]);
}

Food::~Food()
{
    delete pixmap_;
    delete foodpix_;

    foodpix_ = nullptr;
    pixmap_ = nullptr;
}
