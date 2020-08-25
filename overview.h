#ifndef OVERVIEW_H
#define OVERVIEW_H
#include <QPixmap>

class OverView
{
public:
    OverView();
    ~OverView();
    inline const QPixmap* pixmap(){return pixmap_;}
private:
    QPixmap * pixmap_;

};

#endif // OVERVIEW_H
