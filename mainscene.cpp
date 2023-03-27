#include "mainscene.h"
#include "ui_mainsence.h"
#include<QPainter>
#include"MyPushButton.h"
#include<QTimer>
#include<QSound>//多媒体音效头文件
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainSence)
{
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/r/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始音效
    QSound*startSound=new QSound(":/r/res/TapButtonSound.wav",this);
    QSound*Sound=new QSound(":/r/res/myDouDZ.wav",this);

    Sound->setLoops(-1);
    Sound->play();

    //开始按钮
    MyPushButton*startbtn=new MyPushButton(":/r/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);

    choosescene=new ChooseLeveScene;
    //监听选择关卡的返回按钮的信号
    connect(choosescene,&ChooseLeveScene::chooseSceneBack,this,[=](){
        this->setGeometry(choosescene->geometry());
        choosescene->hide();//隐藏选择关卡场景
;        this->show();
        //重新显示主场景

    });
    connect(startbtn,&MyPushButton::clicked,[=](){
        //做一个弹起特效
        startSound->play();
        Sound->stop();
        startbtn->zoom1();
        startbtn->zoom2();

        //延时进入到选择关卡的场景中
        QTimer::singleShot(500,this,[=](){
            //设置choosescene场景的位置
            choosescene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡的场景
            choosescene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/r/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景上图标
    pix.load(":/r/res/Title.png");
    //painter.drawPixmap(0,0,pix);

    //缩放代码
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}

