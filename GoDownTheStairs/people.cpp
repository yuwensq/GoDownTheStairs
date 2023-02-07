#include "people.h"

People::People()
{
    x=0;
    y=0;
    width=40;
    speed=5;
    left=false;
    right=false;
    v=3;
    blood=12;
    luo=false;
    changePerson=0;
}

void People::setPeople(int xx, int yy)
{
    x=xx;
    y=yy;
    width=40;
    v=3;
    left=right=false;
    blood=12;
    luo=false;
    changePerson=0;
    speed=5;
}

People::~People()
{

}

bool People::hasPeople()
{
    if(x!=0)
        return true;
    return false;
}

QRect People::mkRect()
{
    QRect rect(x,y,40,width);
    return rect;
}

bool People::goLeft()
{
    if(left==true)
        return true;
    return false;
}

bool People::goRight()
{
    if(right==true)
        return true;
    return false;
}

bool People::wheLuo()
{
    if(luo==false)
        return false;
    return true;
}

void People::changeChangePerson(char c,int P)
{
    switch(c)
    {
    case '+':changePerson+=P;break;
    case '%':changePerson%=P;break;
    }
}

int People::getChangePerson()
{
    return changePerson;
}

int People::getX()
{
    return x;
}

void People::setX(int xx)
{
    x=xx;
}

int People::getY()
{
    return y;
}

void People::setY(int yy)
{
    y=yy;
}

void People::setLuo(bool Luo)
{
    luo=Luo;
}

void People::runLeft()
{
    x=x-speed>=25?x-speed:25;
}

void People::runRight()
{
   x=x+speed<=515?x+speed:515;
}

int People::getV()
{
    return v;
}

void People::delBlood()
{
    blood=blood-5>=0?blood-5:0;
}

void People::addBlood()
{
    blood=blood+1<=12?blood+1:12;
}

void People::moveWithStairL()
{
    x=x-v/2-1>=25?x-v/2-1:25;
}

void People::moveWithStairR()
{
    x=x+v/2+1<=515?x+v/2+1:515;
}

void People::setMoveDirection(int dir)
{
    if(dir==1)
        left=true;
    else
        right=true;
}

void People::stayStatic()
{
    left=right=false;
}

int People::getBlood()
{
    return blood;
}

int People::getBottom()
{
    return y+40;
}

int People::getRight()
{
    return x+40;
}

void People::setBottom(int yy)
{
    y=yy-40;
}
