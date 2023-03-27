#include "mycoin.h"
#include<QDebug>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnimg)
{
    QPixmap pix;
    bool ret=pix.load(btnimg);
    if(!ret)
    {
        QString str=QString("图片 %1 加载失败").arg(btnimg);
        qDebug()<<str;
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1=new QTimer(this);
    timer2=new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/r/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断，如果翻完了，将min重置为一
        if(this->min>this->max)
        {
            this->min=1;
            timer1->stop();
            isAnimation=false;//停止做动画
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/r/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //判断，如果翻完了，将min重置为一
        if(this->min>this->max)
        {
            this->max=8;
            timer2->stop();
            isAnimation=false;//停止做动画
        }
    });
}

//改变正反面的方法
void MyCoin::changFlag()
{
    //如果是正面，翻成反面
    if(this->flag&!this->isAnimation&!this->iswin)
    {
        timer1->start(30);
        isAnimation=true;//开始做动画
        this->flag=false;
    }
    else if(!this->flag&!this->isAnimation&!this->iswin)
    {
        timer2->start(30);
        isAnimation=true;//开始做动画
        this->flag=true;
    }
}
