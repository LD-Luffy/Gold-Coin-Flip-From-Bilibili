#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include"MyPushButton.h"
#include<QPushButton>
#include<QTimer>
#include<QLabel>
#include<QFont>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum)
{
    this->levelIndex=levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/r/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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

    //返回按钮
    MyPushButton*backbtn=new MyPushButton(":/r/res/BackButton.png",":/r/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    QSound*backSound=new QSound(":/r/res/BackButtonSound.wav",this);
    QSound*flipSound=new QSound(":/r/res/ConFlipSound.wav",this);
    QSound*winSound=new QSound(":/r/res/LevelWinSound.wav",this);

    //点击返回
    connect(backbtn,&MyPushButton::clicked,[=](){
        backSound->play();
      QTimer::singleShot(500,this,[=](){
        emit this->chooseSceneBack();
      });
    });

    //显示当前的关卡数
    QLabel*label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //将字体设置到标签控件中
    label->setFont(font);
    QString str=QString("Level:%1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));//设置大小和位置

    dataConfig config;
    //初始话每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel*winLabel=new QLabel;
    winLabel->setParent(this);
    QPixmap tmpPix;
    tmpPix.load(":/r/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图片
            QLabel*label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/r/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                //显示金币
                str=":/r/res/Coin0001.png";
            }
            if(this->gameArray[i][j]==0)
            {
                str=":/r/res/Coin0008.png";
            }
            MyCoin*coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币的属性赋值
            coin->posx=i;
            coin->posy=j;
            coin->flag=this->gameArray[i][j];

            //将金币放入到金币的二维数组里以便于后期 的维护
            coinbtn[i][j]=coin;
            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                flipSound->play();
                coin->changFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

                QTimer::singleShot(300,this,[=](){
                    //翻转周围的硬币
                    if(coin->posx+1<=3)//右侧金币翻转条件
                    {
                        coinbtn[coin->posx+1][coin->posy]->changFlag();
                        this->gameArray[coin->posx+1][coin->posy]=this->gameArray[coin->posx+1][coin->posy]==0?1:0;
                    }
                    if(coin->posx-1>=0)//左侧金币翻转条件
                    {
                        coinbtn[coin->posx-1][coin->posy]->changFlag();
                        this->gameArray[coin->posx-1][coin->posy]=this->gameArray[coin->posx-1][coin->posy]==0?1:0;
                    }
                    if(coin->posy-1>=0)//上侧金币翻转条件
                    {
                        coinbtn[coin->posx][coin->posy-1]->changFlag();
                        this->gameArray[coin->posx][coin->posy-1]=this->gameArray[coin->posx][coin->posy-1]==0?1:0;
                    }
                    if(coin->posy+1<=3)//下侧金币翻转条件
                    {
                        coinbtn[coin->posx][coin->posy+1]->changFlag();
                        this->gameArray[coin->posx][coin->posy+1]=this->gameArray[coin->posx][coin->posy+1]==0?1:0;
                    }

                    //判断是否胜利
                    this->iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinbtn[i][j]->flag==false)
                            {
                                this->iswin=false;
                                break;
                            }
                        }
                    }
                    if(this->iswin==true)
                    {
                        winSound->play();
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                    coinbtn[i][j]->iswin=true;
                            }
                        }
                        //将胜利图片移动下来
                        QPropertyAnimation*animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/r/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/r/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}
