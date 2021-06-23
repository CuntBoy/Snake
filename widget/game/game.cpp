#include "game.h"
#include "startview.h"
#include <QPainter>
#include "fieldview.h"
#include "food.h"
#include <QThread>
#include "data.h"
#include "snake.h"
#include "SnakeEnum.h"
#include <QDebug>
#include "overview.h"


bool flag = true;

Game::Game(QPixmap * pixmap,QObject *parent)
    : QObject(parent),pixmap_(pixmap),snakedirect(SD::Right) //默认朝向 向右
{
    startview_ = new StartView;
    field_ = new FieldView;
    food_ = new Food;
    overview = new OverView;
    snake = new Snake;
}


// 绘制 开始界面
void Game::drawStartSlot()
{
    Data::instance()->setStatus(GT::Start);
    QPainter painter;
    painter.begin(pixmap_);
    painter.drawPixmap(0,0,*(startview_->getpixmap()));
    painter.end();
    emit finish();
}

// 绘制游戏场景
void Game::drawFieldViewSlot()
{
    QPainter painter;
    painter.begin(pixmap_);
    painter.drawPixmap(0,0,*(field_->getpixmap()));
    painter.end();
    emit finish();
}

// 绘制一帧
void Game::drawOneFrame()
{
    drawFieldViewSlot();  //  游戏场景
    QPainter painter;
    painter.begin(pixmap_);
    // 场景
    // painter.drawPixmap(0,0,*(field_->getpixmap()));

    // 食物
    painter.drawPixmap(0,0,*(food_->draw()));

    // 绘制蛇
    painter.drawPixmap(0,0,*(snake->draw()));

    // game over
    painter.end();
    emit finish();
}

void Game::TurnTo(SD::SnakeDirection direct)
{
//    qDebug()<<__FUNCTION__<<endl;
//    if(flag)
//        snake->TurnTo(direct);
//    flag = false;

    // 设置蛇转向
    snakedirect = direct;
}

// 更新数据
void Game::gameUpdate()
{
    snake->TurnTo(snakedirect);

    if(food_->getpos() == snake->nextHead())
    {
        snake->addItem();
        food_->update(snake->remainPos());
//        this->food_->update();
    }
    else
    {
        bool ret = snake->move();
        if(!ret)
        {
            Data::instance()->setStatus(GT::Over);
            drawOneFrame();
            drawOverView();
            snake->remainPos();
        }
    }
}

void Game::drawOverView()
{
    QPainter painter;
    painter.begin(pixmap_);
    painter.drawPixmap(0,0,*(overview->pixmap()));
    painter.end();
    emit finish();
}

// 动画
void Game::drawGameSlot()
{
    if(Data::instance()->getStatus() == GT::Over || Data::instance()->getStatus() == GT::Start)
    {
        snake->reset();
        food_->update(snake->remainPos());
        snakedirect = SD::Right;
    }

    Data::instance()->setStatus(GT::Running);

    while(Data::instance()->getStatus() == GT::Running)
    {
        drawOneFrame();
        QThread::msleep(200);
        gameUpdate();
    }

}

Game::~Game()
{
    delete startview_;
    delete field_;
    delete food_;
    delete snake;
    delete overview;

    startview_ = nullptr;
    field_ = nullptr;
    food_ = nullptr;
    snake = nullptr;
    overview = nullptr;
}


