#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QKeyEvent;
class Game;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    ~Widget();
signals:
    void drawFieldSignal();
    void drawStartView();
private:
    QPixmap * pixmap_;
    Game * game_;
    QThread * thread_;
};

#endif // WIDGET_H
