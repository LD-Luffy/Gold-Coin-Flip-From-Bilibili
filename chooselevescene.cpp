#include "chooselevescene.h"
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include"MyPushButton.h"
#include"playscene.h"
#include<QSound>
ChooseLeveScene::ChooseLeveScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/r/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar*bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu*startmenu=bar->addMenu("开始");

    //创建退出 菜单项
    QAction*quitAction=startmenu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound*startSound=new QSound(":/r/res/TapButtonSound.wav",this);
    QSound*backSound=new QSound(":/r/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton*backbtn=new MyPushButton(":/r/res/BackButton.png",":/r/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    //点击返回
    connect(backbtn,&MyPushButton::clicked,[=](){
        backSound->play();
        //告诉主场景 我返回了，主场景监听chooselevelscene的返回按钮
      QTimer::singleShot(500,this,[=](){
        emit this->chooseSceneBack();
      });
    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton*menubtn=new MyPushButton(":/r/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(25+i%4*70,130+i/4*70);
        connect(menubtn,&MyPushButton::clicked,[=](){
            startSound->play();
            menubtn->zoom1();
            menubtn->zoom2();

            //进入游戏场景
            play=new PlayScene(i+1);//创建游戏场景
            QTimer::singleShot(500,this,[=](){
                play->setGeometry(this->geometry());
                this->hide();//将关卡场景隐藏掉
                play->show();//显示游戏场景

                connect(play,&PlayScene::chooseSceneBack,[=](){
                    this->setGeometry(play->geometry());
                    this->show();
                    delete play;
                    play=NULL;
                });

            });
        });

        QLabel*label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);

        //设置label上的文字对齐方式 水平居中 垂直居中
        label->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
        //设置让鼠标进行穿透 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}

void ChooseLeveScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/r/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/r/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);


}
