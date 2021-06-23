#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Widget;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void initMenu();  //初始化菜单

private:
    Widget *widget_;   // center widget

public slots:
    void startSlot(); // start
};
#endif // MAINWINDOW_H
