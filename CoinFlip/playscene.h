#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum); //构造函数

    int levelIndex;//内部成员属性  记录所选的关卡

    //重写绘图事件  画背景
    void paintEvent(QPaintEvent *);

    int gameArray[4][4];//二维数组， 维护每个关卡的具体数据

    //将金币放入二维数组中，以便后续维护
    MyCoin * coinBtn[4][4];

    //是否胜利的标志
    bool isWin;

 signals:
    void chooseSceneBack();//自定义返回BACK信号
};

#endif // PLAYSCENE_H
