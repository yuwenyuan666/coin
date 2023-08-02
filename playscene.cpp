#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QTimer>
#include "mypushbutton.h"
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}


PlayScene::PlayScene(int levelIndex)
{
    //记录用户具体选的关卡号
    this->levelIndex = levelIndex;

    //qDebug() << "用户选择的是" << this->levelIndex << "关" ;

    //设置窗口固定大小
    this->setFixedSize(320,588);

    //设置图表
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("翻金币游戏场景");

    //创建菜单栏
    QMenuBar *bar = this->menuBar();
    this->setMenuBar(bar);

    //创建开始菜单栏
    QMenu * startMenu = bar->addMenu("开始");

    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮音效
     QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
     QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
     //胜利按钮音效
     QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);

    //创建返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height() - backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
       // qDebug() << "返回原场景" ;

        //放音效
        backSound->play();
        QTimer::singleShot(500,this,[=](){

            emit this->chooseSceneBack();
        });

    });


    //创建用户具体选择的关卡标签
    QLabel * label = new QLabel;
    label->setParent(this);

    QString str = QString("level: %1").arg(this->levelIndex);
    label->setText(str);


    //设置字体和字号
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);

    label->setFont(font);
    //设置位置和大小
    label->setGeometry(QRect(30,this->height() - 50,120,50));

    //初始化二维数组
    dataConfig config;

    for(int i = 0;i < 4;i ++){
        for(int j = 0;j < 4;j ++){
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片

    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //创建金币背景图片
    for(int i = 0;i < 4; i ++){
        for(int j = 0;j < 4;j ++){
            QLabel * label = new QLabel;
           // label->setGeometry(0,0,50,50);
            QPixmap pix;
            pix.load(":/res/BoardNode.png");

            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i*pix.width(),200+j * pix.height());

            QString str;
            if(this->gameArray[i][j] == 1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            //创建金币
            MyCoin  * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i * pix.width(),204 + j * pix.height());

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //将金币放到二维数组中去
            coinBtn[i][j] = coin;

            //监听点击按钮 信号
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币音效
                flipSound->play();
                //将所有按钮屏蔽点击
                for(int i = 0;i < 4;i ++){
                    for(int j = 0;j < 4;j ++){
                        coinBtn[i][j]->isWin = true;
                    }
                }
               coin->changeFlag();
               //同步二维数组，如果以后有保存需求，可以用数组进行还原
               this->gameArray[i][j] = this->gameArray[i][j] = 1 ? 0 : 1;

               //延时反转周围硬币
               QTimer::singleShot(300,[=](){
                   if(coin->posX + 1 <= 3)
                   {
                       coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] = 1 ? 0 : 1;
                   }
                   //检测左侧金币可否反转
                   if(coin->posX - 1 >= 0)
                   {
                       coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] = 1 ? 0 : 1;
                   }

                   //检测下侧金币是否可否翻转
                   if(coin->posY + 1 <= 3)
                   {
                       coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY + 1] = 1 ? 0 : 1;

                   }
                   if(coin->posY - 1 >= 0)
                   {
                       coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY - 1] = 1 ? 0 : 1;

                   }
                   for(int i = 0;i < 4;i ++){
                       for(int j = 0;j < 4;j ++){
                           coinBtn[i][j]->isWin = false;
                       }
                   }

                   //检测是否胜利
                   isWin = true;
                   for(int i = 0;i < 4;i ++){
                       for(int j = 0;j < 4;j ++){
                           if(coinBtn[i][j]->flag == false)
                           {
                               isWin = false;
                               break;
                           }
                       }
                   }
                   if(isWin)
                   {
                       //qDebug() << "游戏胜利了";
                       winSound->play();
                       for(int i = 0;i < 4;i ++){
                           for(int j = 0;j < 4;j ++){
                               coinBtn[i][j]->isWin = true;
                           }
                       }
                       //将胜利图片做动画
                       QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                       animation1->setDuration(1000);
                       animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                       animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                       animation1->setEasingCurve(QEasingCurve::OutBounce);
                       animation1->start();


                   }
               });


            });
        }
    }
}

//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);

    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
