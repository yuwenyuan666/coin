#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QPixmap>
#include <QMainWindow>
#include <QPainter>
#include <chooselevelscene.h>
namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    //设置绘图事件
    void paintEvent(QPaintEvent *);

    //维护选择场景关卡的指针
    ChooseLevelScene * chooseScene;
private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
