#include "mycoin.h"
#include <QDebug>
#include <QSize>
#include <QPixmap>
#include <Qtimer>
//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}
MyCoin::MyCoin(QString imgPath)
{
    QPixmap pix;
    bool ret = pix.load(imgPath);
    if(!ret)
    {
        qDebug() << "图片加载失败" << imgPath;
        return;
    }


    this->setFixedSize(pix.width(),pix.height());

    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));

    //创建俩个定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1.png").arg(this->min++);

       bool ret = pix.load(str);
       if(!ret)
       {
           qDebug() << "图片加载失败" << imgPath;
           return;
       }

       this->setFixedSize(pix.width(),pix.height());

       this->setStyleSheet("QPushButton{border:0px;}");

       this->setIcon(pix);

       this->setIconSize(QSize(pix.width(),pix.height()));

       if(this->min > this->max)
       {
           this->min = 1;
           //将做动画的标志改为false
           this->isAnimation = false;
           timer1->stop();
       }
    });


    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        bool ret = pix.load(str);
        if(!ret)
        {
            qDebug() << "图片加载失败" << imgPath;
            return;
        }
        this->setFixedSize(pix.width(),pix.height());

        this->setStyleSheet("QPushButton{border:0px;}");

        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min)
        {
            this->max = 8;
            //将做动画的标志改为false
            this->isAnimation = false;
            timer2->stop();
        }
    });





}
void MyCoin::changeFlag()
{
    //如果是金币的标志改为银币
    if(this->flag)
    {
        timer1->start(30);

        //正在做动画，将值改为true
        this->isAnimation = true;
        this->flag = false;
    }
    else
    {
        //如果是银币的标志改为金币
        timer2->start(30);
        //正在做动画，将值改为true
        this->isAnimation = true;
        this->flag = true;
    }
}

//重写鼠标按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{

    //如果做动画这期间不响应
    if(this->isAnimation || this->isWin )
    {
        return ;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
