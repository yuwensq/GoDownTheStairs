#ifndef STAIR
#define STAIR
#include<QRect>
class stair{
    //struct {int x=0;int y=0;int width=0;int type=1;int changeP=0;int stepTime=0;bool isSolid=true;} stairs[8];
private:
    int x;
    int y;
    int width;
    int type;
    int changeP;
    int stepTime;
    bool isSolid;
public:
    stair();
    void setStair(int,int,int wwidth=0,int ttype=1,int cchangeP=0,bool iissolid=true,int ssteptime=0);
    bool hasStair();
    int getType();
    QRect mkRect();
    int getChangeP(int opt=0);
    void setChangeP(int);
    int getY();
    void setY(int);
    void delY(int);
    int getX();
    void setX(int);
    int getWidth();
    void setWidth(int);
    void delWidth(int);
    bool wheSolid();
    void setSolid(bool);
    int getStepTime();
    void plusStepTime();
    int getRight();
};
#endif // STAIR

