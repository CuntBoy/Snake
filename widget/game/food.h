#ifndef FOOD_H
#define FOOD_H
#include "item.h"
#include <QPixmap>

class Food : public Item
{
public:
    Food();
    ~Food();
    void update();
    QPixmap *draw();
    inline QPixmap * getpixmap(){return pixmap_;}
    void update(const QList<QPoint> &list);
private:
    QPixmap * pixmap_;
    QPixmap * foodpix_;
};

#endif // FOOD_H
