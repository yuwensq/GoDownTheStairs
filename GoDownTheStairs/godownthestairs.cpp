#include "godownthestairs.h"
#include "ui_godownthestairs.h"
#include "start.h"
#include "stair.h"
#include <QPainter>
#include <QPalette>
#include <QTimer>
#include <QRect>
#include <QKeyEvent>
#include <cstdlib>
#include <ctime>
#include <QPixmap>
#include <QDialog>
#include <QtDebug>
#include <QColor>
#include <QSound>
#include <QProgressBar>
#include <QIcon>
#include <QLabel>
#include <QFont>

bool singlep=false,doublep=false;
GoDownTheStairs::GoDownTheStairs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoDownTheStairs),blsRun(false)
{
    ui->setupUi(this);
    this->setGeometry(QRect(600,300,795,560));
    this->setFixedSize(795,560);
    QIcon *ico=new QIcon(":/images/img/App.ico");
    this->setWindowIcon(*ico);
    start *s=new start();
    s->setFixedSize(450,300);
    s->setWindowModality(Qt::ApplicationModal);
    s->show();
    setFocusPolicy(Qt::StrongFocus);
    startsound=new QSound("C:\\Users\\Lenovo\\Desktop\\C++ Big Homework\\GoDownTheStairs\\a.wav",this);
    startsound->setLoops(-1);
    ui->label_p1_life->setVisible(false);
    ui->label_p2_life->setVisible(false);
    speed=2;
}

GoDownTheStairs::~GoDownTheStairs()
{
    delete ui;
}

void GoDownTheStairs::paintEvent(QPaintEvent *event)
{
    if(blsRun==false)
        InitStairs(1);
    if(singlep==true)
    {
        startsound->play();
        playMusic=true;
        startRecord=true;
        singlep=false;
        InitPeople(1);
        InitStairs(0);
    }
    else if(doublep==true)
    {
        startsound->play();
        playMusic=true;
        startRecord=true;
        doublep=false;
        InitPeople(2);
        InitStairs(0);
    }
    DrawGameBackground();
}

void GoDownTheStairs::DrawGameBackground()
{
    QPainter painter(this);
    //画游戏背景。
    painter.setPen(Qt::black);//设置画笔颜色。①
    painter.setBrush(Qt::darkGray);//设置填充颜色。①
    painter.drawRect(0,15,795,545);//画的范围。①
    painter.setPen(Qt::black);//设置画笔颜色。②
    painter.setBrush(Qt::black);//设置填充颜色。②
    painter.drawPixmap(5,20,785,535,QPixmap(":/images/img/wholebackground.png"));
    //painter.drawRect(5,20,785,535);//画的范围。②
    painter.setPen(Qt::black);//设置画笔颜色。③
    painter.setBrush(Qt::darkGray);//设置填充颜色。③
    painter.drawRect(20,90,540,455);//画的范围。③
    painter.setPen(Qt::black);//设置画笔颜色。④
    painter.setBrush(QColor(0,0,82));//设置填充颜色。④
    painter.drawPixmap(25,95,530,445,QPixmap(":/images/img/background.png"));
    //painter.drawRect(25,95,530,445);//画的范围。④
    /*//画辅助格子
    painter.setPen(Qt::red);
    //画横线
    for(int i=1;i<=445/40;i++)
        painter.drawLine(25,95+i*40,555,95+i*40);
    //画竖线
    for(int i=1;i<=530/120;i++)
        painter.drawLine(25+i*120,95,25+i*120,540);
    */
    //画楼梯
    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    for(int i=0;i<8;i++)
    {
        if(stairs[i].hasStair()==false)
            break;
        /*switch(stairs[i].getType())
        {
        case 1:painter.setBrush(QColor(118,139,212));break;
        case 2:painter.setBrush(QColor(196,196,196));break;
        case 3:painter.setBrush(QColor(0,246,224));break;
        case 4:painter.setBrush(QColor(255,111,0));break;
        case 5:painter.setBrush(QColor(175,173,156));break;
        }*/
        QRect rect=stairs[i].mkRect();
       // painter.drawRect(rect);
        switch(stairs[i].getType())
        {
        case 1:painter.drawPixmap(rect,QPixmap(":/images/img/stair1.png"));break;
        case 2:painter.drawPixmap(rect,QPixmap(":/images/img/stair2.png"));break;
        case 3:{if(stairs[i].getChangeP()%16>7){painter.drawPixmap(rect,QPixmap(":/images/img/stair3_1.png"));}
                else painter.drawPixmap(rect,QPixmap(":/images/img/stair3_2.png"));
                stairs[i].setChangeP(16);
               };break;
        case 4:{if(stairs[i].getChangeP()%16>7){painter.drawPixmap(rect,QPixmap(":/images/img/stair4_1.png"));}
                else painter.drawPixmap(rect,QPixmap(":/images/img/stair4_2.png"));
                stairs[i].setChangeP(16);
               };break;
        case 5:{
                if(stairs[i].getChangeP(1)==0){painter.drawPixmap(rect,QPixmap(":/images/img/stair5_1.png"));}
                else if(stairs[i].getChangeP(1)<5){rect.setHeight(40);rect.setTop(stairs[i].getY()-10);painter.drawPixmap(rect,QPixmap(":/images/img/stair5_2.png"));}
                else if(stairs[i].getChangeP(1)<10){rect.setHeight(40);rect.setTop(stairs[i].getY()-10);painter.drawPixmap(rect,QPixmap(":/images/img/stair5_3.png"));}
                else if(stairs[i].getChangeP(1)<15){rect.setHeight(40);rect.setTop(stairs[i].getY()-10);painter.drawPixmap(rect,QPixmap(":/images/img/stair5_4.png"));}
                else if(stairs[i].getChangeP(1)<20){rect.setHeight(40);rect.setTop(stairs[i].getY()-10);painter.drawPixmap(rect,QPixmap(":/images/img/stair5_5.png"));}
                else if(stairs[i].getChangeP(1)<25){rect.setHeight(40);rect.setTop(stairs[i].getY()-10);painter.drawPixmap(rect,QPixmap(":/images/img/stair5_6.png"));}
                if(stairs[i].wheSolid()==false)
                {
                    stairs[i].getChangeP();
                    stairs[i].setChangeP(25);
                    if(stairs[i].getChangeP(1)==0)
                        stairs[i].setSolid(true);
                }
               };break;
        }
    }
    painter.drawPixmap(19,90,530,40,QPixmap(":/images/img/ceil.png"));//画房顶
    if(p1.hasPeople())
    {
        painter.setBrush(Qt::red);
        QRect rect=p1.mkRect();
        //painter.drawRect(rect);
        if(p1.goLeft())
        {
            p1.changeChangePerson('+',1);
            if(p1.getChangePerson()%8<=1)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_left_1.png"));
            else if(p1.getChangePerson()%8<4)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_left_2.png"));
            else if(p1.getChangePerson()%8<6)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_left_3.png"));
            else
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_left_2.png"));
            p1.changeChangePerson('%',8);
        }
        else if(p1.goRight())
        {
            p1.changeChangePerson('+',1);
            if(p1.getChangePerson()%8<=1)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_right_1.png"));
            else if(p1.getChangePerson()%8<4)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_right_2.png"));
            else if(p1.getChangePerson()%8<6)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_right_3.png"));
            else
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_right_2.png"));
            p1.changeChangePerson('%',8);
        }
        else if(p1.wheLuo()==true)
        {
            p1.changeChangePerson('+',1);
            if(p1.getChangePerson()%4<1)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_down_1.png"));
            else if(p1.getChangePerson()%4<2)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_down_2.png"));
            else if(p1.getChangePerson()%4<3)
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_down_3.png"));
            else
                painter.drawPixmap(rect,QPixmap(":/images/img/P1_down_2.png"));
            p1.changeChangePerson('%',4);
        }
        else
            painter.drawPixmap(rect,QPixmap(":/images/img/P1_static.png"));
    }
    if(p2.hasPeople()==true)
    {
        painter.setBrush(Qt::red);
        QRect rect=p2.mkRect();
        //painter.drawRect(rect);
        if(p2.goLeft())
        {
            p2.changeChangePerson('+',1);
            if(p2.getChangePerson()%8<=1)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_left_1.png"));
            else if(p2.getChangePerson()%8<4)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_left_2.png"));
            else if(p2.getChangePerson()%8<6)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_left_3.png"));
            else
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_left_2.png"));
            p2.changeChangePerson('%',8);
        }
        else if(p2.goRight())
        {
            p2.changeChangePerson('+',1);
            if(p2.getChangePerson()%8<=1)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_right_1.png"));
            else if(p2.getChangePerson()%8<4)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_right_2.png"));
            else if(p2.getChangePerson()%8<6)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_right_3.png"));
            else
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_right_2.png"));
            p2.changeChangePerson('%',8);
        }
        else if(p2.wheLuo()==true)
        {
            p2.changeChangePerson('+',1);
            if(p2.getChangePerson()%4<1)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_down_1.png"));
            else if(p2.getChangePerson()%4<2)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_down_2.png"));
            else if(p2.getChangePerson()%4<3)
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_down_3.png"));
            else
                painter.drawPixmap(rect,QPixmap(":/images/img/P2_down_2.png"));
            p2.changeChangePerson('%',4);
        }
        else
            painter.drawPixmap(rect,QPixmap(":/images/img/P2_static.png"));
    }
    if(whetherBreak==true)
        painter.drawPixmap(205,260,163,62,QPixmap(":/images/img/pause.png"));
    return;
}

void GoDownTheStairs::InitStairs(int num=1)
{
    blsRun=true;
    stairs[0].setStair(235,520,20,1,0,true,0);
    /*stairs[0].x=235;
    stairs[0].y=520;
    stairs[0].width=20;
    stairs[0].type=1;
    stairs[0].changeP=0;
    stairs[0].isSolid=true;
    stairs[0].stepTime=0;*/
    for(int i=1;i<8;i++)
    {
        stairs[i].setStair(0,0);
        /*stairs[i].x=0;
        stairs[i].changeP=0;
        stairs[i].isSolid=true;
        stairs[i].stepTime=0;*/
    }
    if(num==0)
        delete timer;
    static int mseconds=28;
    mseconds=mseconds-5>=18?mseconds-5:mseconds;
    timer=new QTimer(this);//设定计时器事件
    timer->start(mseconds);//设定时间ms
    connect(timer,SIGNAL(timeout()),SLOT(PeopleUpDate()));
    connect(timer,SIGNAL(timeout()),SLOT(StairsUpDate()));
    //connect(timer,SIGNAL(timeout()),SLOT(WallsUpDate()));
    return;
}

void GoDownTheStairs::InitPeople(int num=1)
{
    if(num==1)
    {
        p1.setPeople(275,480);
        p2.setPeople(0,0);
        ui->label_p1_life->setGeometry(25,10,80,20);
        ui->label_p1_life->setVisible(true);
        p1_blood=new QProgressBar(this);
        p1_blood->setMinimum(0);
        p1_blood->setMaximum(12);
        p1_blood->setValue(12);
        p1_blood->setGeometry(25,55,122,30);
        p1_blood->setTextVisible(false);
        p1_blood->show();
        ui->label->setText(QString::fromUtf8("层数：%1").arg(floorNumber/8));
    }
    else if(num==2)
    {
        doublePeople=true;
        p1.setPeople(235,480);
        p2.setPeople(315,480);
        ui->label_p1_life->setGeometry(25,10,80,20);
        ui->label_p1_life->setVisible(true);
        p1_blood=new QProgressBar(this);
        p1_blood->setMinimum(0);
        p1_blood->setMaximum(12);
        p1_blood->setValue(12);
        p1_blood->setGeometry(25,50,122,30);
        p1_blood->setTextVisible(false);
        p1_blood->show();
        ui->label_p2_life->setGeometry(400,10,80,20);
        ui->label_p2_life->setVisible(true);
        p2_blood=new QProgressBar(this);
        p2_blood->setMinimum(0);
        p2_blood->setMaximum(12);
        p2_blood->setValue(12);
        p2_blood->setGeometry(400,50,122,30);
        p2_blood->setTextVisible(false);
        p2_blood->show();
        ui->label->setText(QString::fromUtf8("层数：%1").arg(floorNumber/8));
    }
    return;
}

void GoDownTheStairs::StairsUpDate()
{
    if(startRecord)
    {
        totalPlayTime++;
        totalPlayTime%=120000;
    }
    if(totalPlayTime>=12000)
        speed=4;
    else if(totalPlayTime>=6000)
        speed=3;
    static int front=25;
    static int front_type=25;
    srand(rand()*front);
    front=rand();
    srand(rand()*front_type);
    front_type=rand();
    int i=0;
    while(i<8)
    {
        if(i==0)
        {
            if(stairs[i].getY()<=95&&stairs[i].getWidth()>0)
            {
                stairs[i].setY(95);
                stairs[i].delWidth(speed);
                if(stairs[i].getWidth()<=0)
                {
                    stairs[i].setChangeP(stairs[i].getChangeP(1));
                    floorNumber++;
                    if(startRecord)
                        ui->label->setText(QString::fromUtf8("层数：%1").arg(floorNumber/8));
                    for(int i=0;i<7;i++)
                    {
                        stairs[i]=stairs[i+1];
                        stairs[i].delY(speed);
                    }
                    if(stairs[6].getY()+60>540)
                    {
                        stairs[7].setX(0);
                        break;
                    }
                    int x=25+rand()%(385/10)*10;
                    int y=stairs[6].getY()+60;
                    int width=540-y;
                    int type=rand()%8+1;
                    stairs[7].setStair(x,y,width,type>4?1:type+1);
                    //stairs[7].x=x;
                    //stairs[7].y=y;
                    //stairs[7].width=width;
                    /*switch(type)
                    {
                    case 1:stairs[i].type=2;break;
                    case 2:stairs[i].type=3;break;
                    case 3:stairs[i].type=4;break;
                    case 4:{stairs[i].type=5;stairs[i].stepTime=0;stairs[i].changeP=0;};break;
                    default:stairs[i].type=1;
                    }*/
                    break;
                }
            }
            else
                stairs[i].delY(speed);
        }
        else
        {
            if(stairs[i].hasStair()==false)
            {
                if(stairs[i-1].getY()+60>540)
                    break;
                int x=25+rand()%(385/10)*10;
                int y=stairs[i-1].getY()+60;
                int width=540-y;
                int type=rand()%8+1;
                //stairs[i].x=x;
                //stairs[i].y=y;
                //stairs[i].width=width;
                stairs[i].setStair(x,y,width,type>4?1:type+1);
                /*switch(type)
                {
                case 1:stairs[i].type=2;break;
                case 2:stairs[i].type=3;break;
                case 3:stairs[i].type=4;break;
                case 4:{stairs[i].type=5;stairs[i].stepTime=0;stairs[i].changeP=0;};break;
                default:stairs[i].type=1;
                }*/
                break;
            }
            else if(stairs[i].getWidth()<20)
            {
                stairs[i].delY(speed);
                stairs[i].setWidth(stairs[i].getWidth()+speed>20?20:stairs[i].getWidth()+speed);
            }
            else
            {
                stairs[i].delY(speed);
            }
        }
        i++;
    }
    update();
    return;
}

void GoDownTheStairs::PeopleUpDate()
{

    if(p1.hasPeople()==true)
    {
        if(p1.goLeft())
        {
            p1.runLeft();
        }
        else if(p1.goRight())
        {
            p1.runRight();
        }     
        static int v1=0;
        if(v1<=5)
            v1+=p1.getV();
        if(p1.getY()<=95)
        {
            p1.setLuo(true);
            p1.delBlood();
        }
        else
        {
            for(int i=0;i<8;i++)
            {
                if(stairs[i].hasStair()==false)
                    break;
                if(p1.wheLuo())
                {
                    if((((p1.getBottom()+v1>=stairs[i].getY()||p1.getBottom()+v1>=stairs[i].getY()-speed)&&p1.getBottom()<stairs[i].getY()))&&p1.getRight()>=stairs[i].getX()&&p1.getX()<=stairs[i].getRight())
                    {
                        if(stairs[i].wheSolid()==false&&stairs[i].getType()==5)
                            break;
                        p1.setBottom(stairs[i].getY());
                        update();
                        v1=0;
                        p1.setLuo(false);
                        if(stairs[i].getType()==2)
                            p1.delBlood();
                        else
                            p1.addBlood();
                        if(stairs[i].getType()==3)
                            p1.moveWithStairL();
                        if(stairs[i].getType()==4)
                            p1.moveWithStairR();
                        if(stairs[i].getType()==5&&stairs[i].wheSolid()==true)
                            stairs[i].plusStepTime();
                        break;
                    }
                }
                else if(p1.wheLuo()==false)
                {
                    if((p1.getBottom()==stairs[i].getY()+1)&&(p1.getRight()<stairs[i].getX()||p1.getX()>stairs[i].getRight()))
                    {
                        p1.setLuo(true);
                        break;
                    }
                    else if(p1.getBottom()==stairs[i].getY()+1)
                    {
                        p1.setBottom(stairs[i].getY());
                        break;
                    }
                    else if((p1.getBottom()==stairs[i].getY()&&(p1.getRight()<stairs[i].getX()||p1.getX()>stairs[i].getRight())))
                    {
                        p1.setLuo(true);
                        break;
                    }
                    else if(p1.getBottom()==stairs[i].getY())
                    {
                        if(stairs[i].getType()==3)
                            p1.moveWithStairL();
                        if(stairs[i].getType()==4)
                            p1.moveWithStairR();
                        if(stairs[i].getType()==5)
                        {
                            stairs[i].plusStepTime();
                            if(stairs[i].getType()==5&&stairs[i].getStepTime()>=15)
                            {
                                p1.setLuo(true);
                                stairs[i].setStair(stairs[i].getX(),stairs[i].getY(),stairs[i].getWidth(),stairs[i].getType(),1,false,0);
                                //stairs[i].changeP=1;
                                //stairs[i].isSolid=false;
                                //stairs[i].stepTime=0;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(p1.wheLuo()==true)
        {
            p1.setY(p1.getY()+v1);
        }
        else
        {
            p1.setY(p1.getY()-speed);
            v1=p1.getV();
        }
        p1_blood->setValue(p1.getBlood()>0?p1.getBlood():0);
        if(p1.getY()>=500||p1.getBlood()<=0)
        {
            p1.setLuo(false);
            p1_blood->setValue(0);
            if(doublePeople==false||diedPeople==1)
            {
                timer->stop();
                startsound->stop();
                gameover=true;
                ui->pushButton_music->setEnabled(false);
                ui->pushButton_music->setText(QString::fromUtf8("music"));
                ui->pushButton_pause->setEnabled(false);
                ui->pushButton_pause->setText(QString::fromUtf8("暂停"));
            }
            else if(diedPeople==0)
            {
                p1.setX(0);
                diedPeople++;
            }
        }
    }
    if(p2.hasPeople()==true)
    {
        if(p2.goLeft())
        {
            p2.runLeft();
        }
        else if(p2.goRight())
        {
            p2.runRight();
        }
        static int v2=0;
        if(v2<=5)
            v2+=p2.getV();
        if(p2.getY()<=95)
        {
            p2.setLuo(true);
            p2.delBlood();
        }
        else
        {
            for(int i=0;i<8;i++)
            {
                if(stairs[i].hasStair()==false)
                    break;
                if(p2.wheLuo()==true)
                {
                    if((((p2.getBottom()+v2>=stairs[i].getY()||p2.getBottom()+v2>=stairs[i].getY()-speed)&&p2.getBottom()<stairs[i].getY()))&&p2.getRight()>=stairs[i].getX()&&p2.getX()<=stairs[i].getRight())
                    {
                        if(stairs[i].wheSolid()==false&&stairs[i].getType()==5)
                            break;
                        p2.setBottom(stairs[i].getY());
                        update();
                        v2=0;
                        p2.setLuo(false);
                        if(stairs[i].getType()==2)
                            p2.delBlood();
                        else
                            p2.addBlood();
                        if(stairs[i].getType()==3)
                            p2.moveWithStairL();
                        if(stairs[i].getType()==4)
                            p2.moveWithStairR();
                        if(stairs[i].getType()==5&&stairs[i].wheSolid()==true)
                            stairs[i].plusStepTime();
                        break;
                    }
                }
                else if(p2.wheLuo()==false)
                {
                    if((p2.getBottom()==stairs[i].getY()+1)&&(p2.getRight()<stairs[i].getX()||p2.getX()>stairs[i].getRight()))
                    {
                        p2.setLuo(true);
                        break;
                    }
                    else if(p2.getBottom()==stairs[i].getY()+1)
                    {
                        p2.setBottom(stairs[i].getY());
                        break;
                    }
                    else if(p2.getBottom()==stairs[i].getY()&&(p2.getRight()<stairs[i].getX()||p2.getX()>stairs[i].getRight()))
                    {
                        p2.setLuo(true);
                        break;
                    }
                    else if(p2.getBottom()==stairs[i].getY())
                    {
                        if(stairs[i].getType()==3)
                            p2.moveWithStairL();
                        if(stairs[i].getType()==4)
                            p2.moveWithStairR();
                        if(stairs[i].getType()==5)
                        {
                            stairs[i].plusStepTime();
                            if(stairs[i].getStepTime()>=15)
                            {
                                p2.setLuo(true);
                                stairs[i].setStair(stairs[i].getX(),stairs[i].getY(),stairs[i].getWidth(),stairs[i].getType(),1,false,0);
                                //stairs[i].changeP=1;
                                //stairs[i].isSolid=false;
                                //stairs[i].stepTime=0;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(p2.wheLuo()==true)
        {
            p2.setY(p2.getY()+v2);
        }
        else
        {
            p2.setY(p2.getY()-speed);
            v2=p2.getV();
        }
        p2_blood->setValue(p2.getBlood()>0?p2.getBlood():0);
        if(p2.getY()>=500||p2.getBlood()<=0)
        {
            p2.setLuo(false);
            p2_blood->setValue(0);
            if(diedPeople==1)
            {
                ui->pushButton_music->setEnabled(false);
                ui->pushButton_music->setText(QString::fromUtf8("music"));
                ui->pushButton_pause->setEnabled(false);
                ui->pushButton_pause->setText(QString::fromUtf8("暂停"));
                timer->stop();
                startsound->stop();
                gameover=true;
            }
            else
            {
                p2.setX(0);
                diedPeople++;
            }
        }
    }
    update();
    return;
}

void GoDownTheStairs::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent *key=(QKeyEvent*) event;
    switch(key->key())
    {
    case Qt::Key_Left:{if(p1.hasPeople()==true){p1.setMoveDirection(1);}}break;
    case Qt::Key_Right:{if(p1.hasPeople()==true){p1.setMoveDirection(2);}}break;
    case Qt::Key_A:{if(p2.hasPeople()==true){p2.setMoveDirection(1);}}break;
    case Qt::Key_D:{if(p2.hasPeople()==true){p2.setMoveDirection(2);}}break;
    default:break;
    }
    return;
}

void GoDownTheStairs::keyReleaseEvent(QKeyEvent *event)
{
    QKeyEvent *key=(QKeyEvent*) event;
    if(key->isAutoRepeat()==true)
    {
        return;
    }
    else if(key->key()==Qt::Key_Left||key->key()==Qt::Key_Right)
    {
        p1.stayStatic();
    }
    else if(key->key()==Qt::Key_A||key->key()==Qt::Key_D)
    {
        p2.stayStatic();
    }
    return;
}

void GoDownTheStairs::on_pushButton_pause_clicked()
{
    if(whetherBreak==false)
    {        
        ui->pushButton_music->setEnabled(false);
        timer->stop();
        ui->pushButton_pause->setText(QString::fromUtf8("继续"));
        whetherBreak=true;
        startsound->stop();
        update();
    }
    else
    {
        ui->pushButton_music->setEnabled(true);
        timer->start(18);
        ui->pushButton_pause->setText(QString::fromUtf8("暂停"));
        whetherBreak=false;
        startsound->play();
    }
}

void GoDownTheStairs::on_pushButton_restart_clicked()
{
    gameover=false;
    singlep=false,doublep=false;
    doublePeople=false;
    ui->label_p1_life->setVisible(false);
    ui->label_p2_life->setVisible(false);
    if(p1_blood!=NULL)
    {
        delete p1_blood;
        p1_blood=NULL;
    }
    if(p2_blood!=NULL)
    {
        delete p2_blood;
        p2_blood=NULL;
    }
    p1.setX(0);
    p2.setX(0);
    speed=2;
    totalPlayTime=0;
    diedPeople=0;
    ui->pushButton_music->setEnabled(true);
    ui->pushButton_pause->setEnabled(true);
    ui->pushButton_music->setText("music");
    timer->stop();
    startsound->stop();
    floorNumber=0;
    startRecord=false;
    start *s1=new start();
    s1->setFixedSize(450,300);
    s1->setWindowModality(Qt::ApplicationModal);
    s1->show();
}

void GoDownTheStairs::on_pushButton_music_clicked()
{
    if(playMusic&&gameover==false)
    {
        ui->pushButton_music->setText(QString::fromUtf8("quiet"));
        startsound->stop();
        playMusic=false;
    }
    else if(gameover==false)
    {
        ui->pushButton_music->setText(QString::fromUtf8("music"));
        startsound->play();
        playMusic=true;
    }
}
