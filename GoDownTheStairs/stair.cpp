#include<stair.h>
#include<QDebug>
stair::stair()
{
    x=0;
    y=0;
    type=1;
    width=0;
    changeP=0;
    stepTime=0;
    isSolid=true;
}
void stair::setStair(int xx, int yy, int wwidth, int ttype, int cchangeP, bool iissolid, int ssteptime)
{
    x=xx;
    y=yy;
    width=wwidth;
    type=ttype;
    changeP=cchangeP;
    isSolid=iissolid;
    stepTime=ssteptime;
}

bool stair::hasStair()
{
    if(x==0)
        return false;
    return true;
}
int stair::getType()
{
    return type;
}
QRect stair::mkRect()
{
    QRect rect(x,y,120,width);
    return rect;
}
int stair::getChangeP(int opt)
{
    if(opt==0)
        changeP++;
    return changeP;
}
void stair::setChangeP(int mo)
{
    if(mo==0)
        return;
    else
        changeP%=mo;
}
int stair::getY()
{
    return y;
}
void stair::setY(int Y)
{
    y=Y;
}
void stair::delY(int d)
{
    y-=d;
}
int stair::getWidth()
{
    return width;
}
void stair::setWidth(int Width)
{
    width=Width;
}
void stair::delWidth(int D)
{
    width-=D;
}
int stair::getX()
{
    return x;
}
void stair::setX(int xx)
{
    x=xx;
}

void stair::setSolid(bool solid)
{
    isSolid=solid;
}
bool stair::wheSolid()
{
    return isSolid;
}
int stair::getStepTime()
{
    return stepTime;
}
void stair::plusStepTime()
{
    stepTime++;
}
int stair::getRight()
{
    return x+120;
}
