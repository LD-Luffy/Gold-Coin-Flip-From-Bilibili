#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include"chooselevescene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainSence; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写paintevent事件 画背景图
    void paintEvent(QPaintEvent *);

    ChooseLeveScene*choosescene=NULL;
private:
    Ui::MainSence *ui;
};
#endif // MAINSENCE_H
