#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //绘制选择关卡背景
    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    PlayScene * play = NULL;
signals:
    //写一个自定义信号，告诉主场景 ，点击了返回
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
