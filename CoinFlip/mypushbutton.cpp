#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>//创建动画
MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    //成员变量normalImgPath保存正常显示图片路径
    normalImgPath = normalImg;
    //成员变量pressedImgPath保存按下后显示的图片
    pressedImgPath = pressImg;
    //创建QPixmap对象
    QPixmap pix;
    //判断是否能够加载正常显示的图片，若不能提示加载失败
    bool ret = pix.load(normalImgPath);
    if(!ret){
        qDebug()<<normalImg<<"加载图片失败！";
        return;//可有可无
    }
    //设置按钮的固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));



}

void MyPushButton::zoom1() //向下跳跃
{
    //创建动画对象  为一个几何图形
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置动画的时间间隔
    animation1->setDuration(200);//  单位ms
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}

void MyPushButton::zoom2() //向上跳跃
{
    //创建动画对象  为一个几何图形
    QPropertyAnimation * animation2 = new QPropertyAnimation(this,"geometry");
    //设置动画的时间间隔
    animation2->setDuration(200);//  单位ms
    //创建起始位置
    animation2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation2->start();
}
//鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressedImgPath != ""){//选中路径不为空，说需要按下图片
        //创建QPixmap对象
        QPixmap pix;
        //判断是否能够加载正常显示的图片，若不能提示加载失败
        bool ret = pix.load(pressedImgPath);
        if(!ret){
            qDebug()<<pressedImgPath<<"加载图片失败！";
            return;//可有可无
        }
        //设置按钮的固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath != ""){//选中路径不为空，说需要释放图片
        //创建QPixmap对象
        QPixmap pix;
        //判断是否能够加载正常显示的图片，若不能提示加载失败
        bool ret = pix.load(normalImgPath);
        if(!ret){
            qDebug()<<normalImgPath<<"加载图片失败！";
            return;//可有可无
        }
        //设置按钮的固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mouseReleaseEvent(e);
}


