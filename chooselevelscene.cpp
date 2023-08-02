#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QTimer>
#include  <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置菜单栏
    QMenuBar * bar = this->menuBar();

    //创建开始菜单栏
    QMenu * startMenu = bar->addMenu("开始");

    //创建按钮菜单选项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出，退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    this->setFixedSize(320,588);
    this->setWindowTitle("翻金币主场景");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //选中按钮音效
     QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
     //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //创建返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height() - backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
       // qDebug() << "返回原场景" ;
        backSound->play();

        QTimer::singleShot(500,this,[=](){

            emit this->chooseSceneBack();
        });

    });

    playScene = NULL;
    //创建20个关卡的小按钮
    for(int i = 0;i < 20 ;i ++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");

        menuBtn->setParent(this);

        menuBtn->move( 25 + (i%4) * 70,130 + (i / 4) * 70);

        connect(menuBtn,&MyPushButton::clicked,[=](){
           // qDebug()<< "你选择的是第" <<i +1<< "关";
           chooseSound->play();
           playScene = new PlayScene(i + 1);

           this->hide();
           //设置游戏场景位置
           this->playScene->setGeometry(this->geometry());
           this->playScene->show();

           //监听游戏场景中点击返回按钮，发送的自定义信号
           connect(this->playScene,&PlayScene::chooseSceneBack,[=](){
               this->setGeometry(this->playScene->geometry());
               delete this->playScene;
               this->playScene = NULL;
               this->show();
           });

        });
        //创建显示具体的关卡号 Label
        QLabel * label = new QLabel;

        label->setParent(this);;

        label->setFixedSize(menuBtn->width(),menuBtn->height());

        label->setText(QString::number(i+1));

        label->move(25 + (i%4) * 70,130 + (i / 4) * 70);

        //设置居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置鼠标穿透事件   51号  鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);



    }

}

//重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()-pix.width()*0.5,30,pix.width(),pix.height(),pix);

}
