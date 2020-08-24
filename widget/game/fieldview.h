#ifndef FIELDVIEW_H
#define FIELDVIEW_H
#include <QPixmap>

class FieldView
{
public:
    FieldView();
    ~FieldView();
    inline QPixmap * getpixmap(){return pixmap_;}
private:
    QPixmap * pixmap_;
};

#endif // FIELDVIEW_H
