#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{

public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //normalImg 代表正常显示的图片
    //pressImg  代表按下后显示的图片，默认为空
    //构造函数
    MyPushButton(QString normalImg,QString pressImg ="");

    QString normalImgPath; //默认显示图片路径
    QString pressedImgPath; //按下后显示图片的路径

    void zoom1();//向下跳跃
    void zoom2();//向上跳跃

    //重写按钮 按下和释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
