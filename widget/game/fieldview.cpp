#include "fieldview.h"
#include <QPixmap>
#include "data.h"
#include <QPainter>

FieldView::FieldView()
{
    QPixmap cellpixmap(":pic/pic/field.jpg");
    cellpixmap.scaled(Data::instance()->getcellsize(),Data::instance()->getcellsize());
    pixmap_ = new QPixmap(Data::instance()->getsize());

    int row = Data::instance()->getrow();
    int column = Data::instance()->getcolumn();
    int cellsize = Data::instance()->getcellsize();

    int j = 0;
    QPainter painter;
    painter.begin(pixmap_);

    for(int i = 0;i <row;i++)
    {
        for(j = 0;j <column;j++)
            painter.drawPixmap(cellsize*j,cellsize*i,cellpixmap);
    }

    painter.end();



}
FieldView::~FieldView()
{
    delete pixmap_;
}
