#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QSound>//多媒体模块下 的音效头文件
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(320,588);
    //设置应用图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("庞哥快点爆金币");
    //退出按钮实现
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);
//    startSound->setLoops(-1);//设置播放循环 如果-1 代表无限循环
//    startSound->play();
    //创建开始按键
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);

    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡 对象
    chooseScene =new ChooseLevelScene;

    //监听选择关卡的返回按钮
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();//选择关卡隐藏
        this->show();//主场景重新显示
    });

    //实现开始按钮的跳跃特效
    //监听点击事件，执行特效
    connect(startBtn,&QPushButton::clicked,[=](){
        //播放开始的音效
        startSound->play();

        startBtn->zoom1();//向下跳跃
        startBtn->zoom2();//向上跳跃

        //延迟0.5秒  进入下面的过程 --- 方便上面的跳跃动作做完
        QTimer::singleShot(450,this,[=](){
            //设置chooseScene场景的位置
            chooseScene->setGeometry(this->geometry());
            //隐藏开始界面
            this->hide();
            //显示选择关卡界面
            chooseScene->show();
        });

    });


}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");//载入背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题图标
    pix.load(":/res/Title.png");
    //缩放标题图标
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix);






}

