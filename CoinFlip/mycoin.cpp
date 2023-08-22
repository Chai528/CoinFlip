#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    //初始化定时器对象
    timer1 =new QTimer(this);
    timer2 =new QTimer(this);

    //监听正面翻反面的信号  并反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min > this->max){//如果大于最大值，重置最小值，并停止定时器
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号  并反转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max < this->min){//如果小于最小值，重置最大值，并停止定时器
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });

}
//改变正反面标志的方法
void MyCoin::changeFlag()
{
    //如果是正面  翻成反面
    if(this->flag){
        timer1->start(30);//每隔30ms就监听一次
        isAnimation = true;//开始做动画
        this->flag = false;
    }
    else{//如果是反面  翻成正面
        timer2->start(30);
        isAnimation =true;
        this->flag =true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || isWin == true){//如果正在做动画 或者 全胜利标志 ， 鼠标点击就不进行其他的操作，截获
        return;
    }
    else{
        return QPushButton::mousePressEvent(e);//没做动画，就按默认的来
    }
}
