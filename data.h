#ifndef DATA_H
#define DATA_H
namespace GT {
typedef enum type{
    Start,
    Running,
    Pause,
    Over,
    Win
}GameType;

}


#include <QSize>
class Data
{
private:
    Data();
public:
    static Data * instance();
    static void  release();
    inline int getcellsize(){return cellSize_;}
    inline void setcellsize(int size){cellSize_ = size;}
    inline int getrow(){return row_;}
    inline void setrow(int row){row_ = row;}
    inline int getcolumn(){return column_;}
    inline void setcolumn(int column){column_ = column;}
    inline QSize getsize(){return QSize(cellSize_ * column_,cellSize_*row_);}
    inline void setStatus(GT::GameType status){gamestatus_ = status;}
    inline int getStatus(){return gamestatus_;}
    inline QSize cellSize(){return QSize(cellSize_,cellSize_);}
private:
    static Data *data_;
    int cellSize_;
    int row_;
    int column_;
    GT::GameType gamestatus_;


};



#endif // DATA_H
