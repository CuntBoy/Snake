#include "item.h"

Item::Item(QPoint  pos, IType::ItemType type)
    :pos_(pos),type_(type)
{

}

Item::Item()
    :pos_(0,0),type_(IType::Food){}
