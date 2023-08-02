#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QPixmap>

#include <playscene.h>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    PlayScene * playScene;

signals:
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
