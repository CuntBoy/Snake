#ifndef STARTVIEW_H
#define STARTVIEW_H
#include <QPixmap>

class StartView
{
public:
    StartView();
    ~StartView();
    inline QPixmap * getpixmap(){return pixmap_;}
private:
    QPixmap * pixmap_;
};

#endif // STARTVIEW_H
