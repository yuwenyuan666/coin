#include "mypushbutton.h"
//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    //成员变量normalImgPath
    normalImgPath = normalImg;
    pressdImgPath = pressImg;

    //创建QPixmap对象
    QPixmap pixmap;

    //判断是否能够加载出正常显示的图片
    bool ret = pixmap.load(normalImgPath);
    if(!ret)
    {
        QString srt = QString("图片加载失败%|").arg(normalImg);
        qDebug() << normalImg ;
    }

    //设置图片的固定尺寸
    this->setFixedSize(pixmap.width(),pixmap.height());

    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图片
    this->setIcon(pixmap);

    //设置图表大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

}
void MyPushButton::zoom1()
{
    QPropertyAnimation *animation1 = new QPropertyAnimation(this,"geometry");

    animation1->setDuration(200);

    //设置起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation1->setEndValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));;

    //设置缓和曲线
    animation1->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation1->start(QAbstractAnimation::DeleteWhenStopped);

}

void MyPushButton::zoom2()
{
    QPropertyAnimation *animation2 = new QPropertyAnimation(this,"geometry");

    animation2->setDuration(200);

    //设置起始位置
    animation2->setStartValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));

    //设置结束位置
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));;

    //设置缓和曲线
    animation2->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation2->start(QAbstractAnimation::DeleteWhenStopped);


}

//重写鼠标按下
void MyPushButton:: mousePressEvent(QMouseEvent *e)
{
    if(this->pressdImgPath != "")
    {
        //创建QPixmap对象
        QPixmap pixmap;

        //判断是否能够加载出正常显示的图片
        bool ret = pixmap.load(pressdImgPath);
        if(!ret)
        {
            QString srt = QString("图片加载失败%|").arg(pressdImgPath);
            qDebug() << pressdImgPath;
            return;
        }

        //设置图片的固定尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());

        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图片
        this->setIcon(pixmap);

        //设置图表大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    }
    return QPushButton::mousePressEvent(e);
}

//重写鼠标释放
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressdImgPath != "")
    {
        //创建QPixmap对象
        QPixmap pixmap;

        //判断是否能够加载出正常显示的图片
        bool ret = pixmap.load(normalImgPath);
        if(!ret)
        {
            QString srt = QString("图片加载失败%|").arg(normalImgPath);
            qDebug() << normalImgPath ;
            return;
        }

        //设置图片的固定尺寸
        this->setFixedSize(pixmap.width(),pixmap.height());

        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图片
        this->setIcon(pixmap);

        //设置图表大小
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    }
    return QPushButton::mouseReleaseEvent(e);
}
