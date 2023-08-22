#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入到了第 %1 关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex = levelNum;

    //初始化场景设置
    //配置选择关卡 窗口大小
    this->setFixedSize(320,588);
    //配置界面左上角图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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

    //添加音效资源
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);


    //返回按钮
    //创建BACK按钮，由于不是静态的图片，可以在构造函数中写，不在绘图事件中
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"在翻金币场景： 点击了返回";
        //播放返回按钮的音效
        backSound->play();
        //告诉主场景，我返回了，主场景监听 ChooseLevelScene的BACK按钮
        //延时的返回
        QTimer::singleShot(450,this,[=](){
            emit this->chooseSceneBack();//激发BACK返回信号
        });
    });


    //显示当前关卡数（左下角）
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 =QString("Level:%1").arg(this->levelIndex);
    //将字体设置到 标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(25,this->height()-50,122,50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());//隐藏在屏幕上侧

    //显示金币
    for(int i = 0;i<4;i++){
        for(int j = 0; j<4;j++){
            //绘制金币背景
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel *label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i* pix.width(), 200 + j* pix.height());

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1){
                str = ":/res/Coin0001.png";//显示金币
            }
            else{
                str= ":/res/Coin0008.png";//显示银币
            }
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i* pix.width(), 204 + j* pix.height());

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; //   1-正  0-反

            //将coin放入到 金币的二维数组中  ， 以便后续的维护
            coinBtn[i][j] = coin;

            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币音效
                flipSound->play();
                //点击按钮 将所有的按钮都先禁用
                for(int i = 0;i<4;i++){
                    for(int j = 0;j<4;j++){
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1:0;//数组内部记录的标志同步修改

                //周围金币的延迟翻转
                QTimer::singleShot(295,this,[=](){
                    //翻转周围的硬币
                    //翻转周围的  右侧的硬币  判断条件
                    if(coin->posX+1 <= 3){
                        coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1:0;
                    }
                    //翻转周围的  左侧的硬币  判断条件
                    if(coin->posX-1 >= 0){
                        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1:0;
                    }
                    //翻转周围的  下侧的硬币  判断条件
                    if(coin->posY+1 <= 3){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1:0;
                    }
                    //翻转周围的  上侧的硬币  判断条件
                    if(coin->posY-1 >= 0){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1:0;
                    }

                    //翻完周围金币后 将所有的金币解开禁用
                    for(int i = 0;i<4;i++){
                        for(int j = 0;j<4;j++){
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }


                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0;i<4;i++){
                        for(int j = 0;j< 4;j++){
                            if(coinBtn[i][j]->flag == false){//只要有一个是反面  那就算失败
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true){
                        qDebug()<<"胜利了";
                        //播放胜利的音效
                        winSound->play();
                        //将所有的按钮的 胜利标志 置为true; 如果再次点击按钮 ，直接return
                        for(int i = 0;i<4;i++){
                            for(int j = 0;j< 4;j++){
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        //将胜利的图片砸下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+140,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }

                });
            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    //设置背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
