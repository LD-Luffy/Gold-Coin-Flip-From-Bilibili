#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnimg);
    //参数代表传入的是金币路径还是银币路径

    //金币的属性
    int posx;//x坐标位置
    int posy;//y坐标位置
    bool flag;//正反标识

    //改变标志的方法
    void changFlag();
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;//反面翻正面的定时器
    int min=1;
    int max=8;

    //执行动画的标志
    bool isAnimation=false;

    //是否胜利
    bool iswin=false;

signals:

};

#endif // MYCOIN_H
