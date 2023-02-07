#include "godownthestairs.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "QTextCodec"
#include "start.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":decoration.qss");
    if( qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else
    {
        qDebug("Open failed");
    }
    GoDownTheStairs w;
    w.show();
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    return a.exec();
}
