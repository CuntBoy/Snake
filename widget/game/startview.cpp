#include "startview.h"
#include <QPixmap>
#include <data.h>

StartView::StartView()
{
    pixmap_ = new QPixmap(":/pic/pic/main.png");
    *pixmap_ = pixmap_->scaled(Data::instance()->getsize(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}

StartView::~StartView()
{
    delete pixmap_;
    pixmap_ = nullptr;
}
