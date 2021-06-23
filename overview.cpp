#include "overview.h"
#include <QPixmap>
#include "data.h"

OverView::OverView()
{
    pixmap_ = new QPixmap(":pic/pic/gameover.jpg");
    *pixmap_ = pixmap_->scaled(Data::instance()->getsize(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}


OverView::~OverView()
{
    delete pixmap_;
    pixmap_ = nullptr;
}
