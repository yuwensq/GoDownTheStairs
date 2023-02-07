#ifndef GODOWNTHESTAIRS_H
#define GODOWNTHESTAIRS_H

#include <QMainWindow>
//#include "start.h"
#include "stair.h"
#include "people.h"

class QProgressBar;
class QSound;
class stair;
namespace Ui {
class GoDownTheStairs;
}

class GoDownTheStairs : public QMainWindow
{
    Q_OBJECT
public:
    explicit GoDownTheStairs(QWidget *parent = 0);
    ~GoDownTheStairs();
    void paintEvent(QPaintEvent *event);
    void DrawGameBackground();
    void InitStairs(int num);
    void InitPeople(int num);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
public slots:
    void StairsUpDate();
    void PeopleUpDate();

private slots:

    void on_pushButton_pause_clicked();

    void on_pushButton_restart_clicked();

    void on_pushButton_music_clicked();

private:
    Ui::GoDownTheStairs *ui;
    QTimer *timer=NULL;//定时器
    int pdirection;//人的移动方向
    bool blsRun;//是否开始
    stair stairs[8];
    //struct {int x=0;int y=0;int width=0;int speed=5;bool left=false;bool right=false;int v=1;int blood=12;bool luo=false;int changePerson=0;} p1,p2;
    People p1,p2;
    int speed=3;//上升速度
    unsigned long long totalPlayTime=0;
    QProgressBar *p1_blood=NULL,*p2_blood=NULL;
    bool doublePeople=false,diedPeople=0;
    unsigned int floorNumber=0;
    bool startRecord=false;
    QSound *startsound=NULL;
    bool playMusic=false;
    bool gameover=false;
    bool whetherBreak=false;
};

#endif // GODOWNTHESTAIRS_H
