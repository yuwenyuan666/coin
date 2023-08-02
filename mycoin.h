#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);

    //参数显示默认图片显示路径
    MyCoin(QString imgPath);

    //x坐标
    int posX;

    //y坐标
    int posY;

    //正反坐标
    bool flag;

    void changeFlag();
    QTimer * timer1;
    QTimer * timer2;
    int min = 1;
    int max = 8;

    bool isAnimation = false;  //做反转动画的标志

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    bool isWin = false;  //给一个是否胜利的状态值

signals:

public slots:
};

#endif // MYCOIN_H
