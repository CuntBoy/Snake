#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QPixmap>
#include "SnakeEnum.h"

class FieldView;
class StartView;
class Food;
class Snake;
class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QPixmap *pixmap, QObject *parent = nullptr);
    ~Game();


signals:
    void finish();
public slots:
    void drawStartSlot();
    void drawFieldViewSlot();
    void drawOneFrame();
    void drawGameSlot();
    void TurnTo(SD::SnakeDirection direct);
    void gameUpdate();



private:
    QPixmap * pixmap_;
    StartView *startview_;
    FieldView * field_;
    Food * food_;
    Snake * snake;
    SD::SnakeDirection snakedirect;
};

#endif // GAME_H
