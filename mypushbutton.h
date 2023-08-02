#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = 0);


    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;    //默认显示图片路径

    QString pressdImgPath;   //按下后显示图片路径

    //向上弹起
    void zoom1();


    //向下弹起
    void zoom2();

    //重写鼠标按下
    void mousePressEvent(QMouseEvent *);

    //重写鼠标释放
    void mouseReleaseEvent(QMouseEvent *);



signals:

public slots:
};

#endif // MYPUSHBUTTON_H
