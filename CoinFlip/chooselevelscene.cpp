#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡 窗口大小
    this->setFixedSize(320,588);
    //配置界面左上角图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);//放置于当前窗口
    //创建“开始”菜单
    QMenu * startMenu = bar->addMenu("开始");
    QMenu * chaiMenu = bar->addMenu("你龙就是帅啊");
    //创建“退出”按钮
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出 -->退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);


    //创建BACK按钮，由于不是静态的图片，可以在构造函数中写，不在绘图事件中
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&QPushButton::clicked,[=](){
        //播放返回按钮音效
        backSound->play();

        //qDebug()<<"点击了返回";
        //告诉主场景，我返回了，主场景监听 ChooseLevelScene的BACK按钮
        //延时的返回
        QTimer::singleShot(450,this,[=](){
            emit this->chooseSceneBack();//激发BACK返回信号
        });
    });

    //创建选择关卡的按钮
    for(int i = 0;i<20;i++){
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move( 25+i%4*70, 130+ i/4 *70 );

        //监听每个选关的按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //播放选择关卡音效
            chooseSound->play();

            QString str = QString("您选择的是第 %1 关").arg( i + 1 );
            qDebug()<<str;

            //进入到游戏场景
            if(play == NULL){//这个可以删去
                this->hide();//原来的选关场景关闭
                play = new PlayScene(i+1);//创建游戏场景
                //设置游戏场景的初始位置
                play->setGeometry(this->geometry());//  在new创建对象后再设置
                play->show();//显示游戏场景
            }
            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();//显示选择关卡界面
                delete play;
                play = NULL;//销毁那一关卡的对象
            });

        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70, 130+ i/4 *70);
        //设置Label中的字   水平和垂直 居中对齐
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置鼠标事件 穿透 ，从 表层的Label 穿透到 里面的 menuBtn       51号
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    }

}
//绘制事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    //设置背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
