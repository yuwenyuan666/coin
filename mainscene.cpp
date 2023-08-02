#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(320,588);
    this->setWindowTitle("翻金币主场景");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));


    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //开始音效准备
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);


    //选择关卡场景
    chooseScene  = new ChooseLevelScene;


    //创建开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5- startBtn->width() * 0.5,this->height() * 0.7);

    //监听选择中的返回按钮
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        chooseScene->hide();
       this->setGeometry(chooseScene->geometry());
       this->show();
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        //播放音效
        startSound->play(); //开始音效
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            //设置选中关卡的位置
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });



}
void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家指定绘图设备
    QPainter painter(this);
    //创建Pixmap对象
    QPixmap pix;
    // 加载图片
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制背景图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载标题
    pix.load(":/res/Title.png");

    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);

    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
MainScene::~MainScene()
{
    delete ui;
}

