#include "data.h"

Data * Data::data_ = nullptr;
Data::Data()
    :cellSize_(50),row_(10),column_(10),gamestatus_(GT::Start)
{

}
Data * Data::instance()
{
    if(data_ == nullptr)
    {
        data_ = new Data;
    }
    return data_;
}
void Data::release()
{
    if(data_ != nullptr)
    {
        delete data_;
        data_ = nullptr;
        Data::instance()->setStatus(GT::Start);
    }
}
