#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //参数代表 传入的是 金币路径 还是银币路径
    MyCoin(QString btnImg);


    //金币的属性
    int posX;//金币的x坐标
    int posY;//金币的y坐标
    bool flag;//正反的标志  1-正  0-反

    void changeFlag();//改变标志，执行翻转效果
    QTimer *timer1 ;//正面翻反面的定时器
    QTimer *timer2 ;//反面翻正面的定时器
    int min = 1;
    int max = 8;

    //执行动画的标志
    bool isAnimation = false;

    //重写 按下（鼠标狂点，动画来不及做）
    void mousePressEvent(QMouseEvent *);

    //判断是否胜利的标志
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
