#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);

    int levelIndex;//内部成员属性，记录所选关卡

    //重写paintevent事件
    void paintEvent(QPaintEvent*);

    int gameArray[4][4];//二维数组 维护每个关卡的具体数据

    MyCoin*coinbtn[4][4];

    //是否胜利
    bool iswin;
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
