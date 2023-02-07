#include "start.h"
#include "ui_start.h"
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QMessageBox>
#include <QRect>

extern bool singlep,doublep;
start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    ui->setupUi(this);
    ui->label_1->setText("Begin!");
    QIcon *ico=new QIcon(":/images/img/App.ico");
    //setAutoFillBackground(true);
    //QPalette palette;
    //QPixmap pixmap(":/images/img/startbackground.png");
    //palette.setBrush(backgroundRole(),QBrush(pixmap));
    //this->setPalette(palette);
    this->setWindowIcon(*ico);
}

start::~start()
{
    delete ui;
}


void start::on_pushButton_shutdown_clicked()
{

    exit(0);
    delete this;
    return;
}

void start::on_pushButton_single_clicked()
{
    this->close();
    singlep=true;
    delete this;
    return;
}

void start::on_pushButton_double_clicked()
{
    this->close();
    doublep=true;
    delete this;
    return;
}


void start::on_pushButton_help_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromUtf8("一、左右方向键控制P1移动，AD键控制P2移动。\n二、急速转向小人会晕住不动。\n三、楼梯特性请自行探索。(●'◡'●)"));
    QRect rect(710,350,200,200);
    msgBox.setGeometry(rect);
    msgBox.setWindowFlags(Qt::CustomizeWindowHint|Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    msgBox.exec();
}
