#ifndef ITEM_H
#define ITEM_H
#include <QPoint>

namespace IType {
typedef enum{
    Food,
    SnakeHead,
    SnakeBody,
    SnakeTail
} ItemType;
}


class Item
{
public:
    Item();
    Item(QPoint pos, IType::ItemType type = IType::Food);
    inline QPoint getpos(){return pos_;}
    inline int gettype(){return type_;}
    inline void setpos(QPoint pos){pos_ = pos;}
    inline void settype(IType::ItemType type){type_ = type;}
private:
    QPoint pos_;
    IType::ItemType type_;
};

#endif // ITEM_H
