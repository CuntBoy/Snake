#ifndef SNAKE_H
#define SNAKE_H
#include "item.h"
#include <QList>
#include <QPixmap>
#include "SnakeEnum.h"

class SnakeItem:public Item
{
public:
    SnakeItem(QPoint pos, IType::ItemType type,SD::SnakeDirection direct = SD::Right)
        :Item(pos,type),direct_(direct){}
    inline SD::SnakeDirection getDirection(){return direct_;}
    inline void setDirection(SD::SnakeDirection direct){direct_ = direct;}
private:
    SD::SnakeDirection direct_;
};

class Snake
{
public:
    Snake();
    ~Snake();

    void init();
    QPixmap *draw();
    void move();
    void TurnTo(SD::SnakeDirection direct);
    void addItem();
    QPoint nextHead();
private:
    QList<SnakeItem> list_;
    QPixmap * pixmap_;
    QPixmap * pixhead_;
    QPixmap * pixbody_;
    QPixmap * pixtail_;
private:

    QPixmap rotate(QPixmap *pixmap, SD::SnakeDirection direct);
};

#endif // SNAKE_H
