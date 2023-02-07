#ifndef PEOPLE_H
#define PEOPLE_H
#include<QRect>
//struct {int x=0;int y=0;int width=0;int speed=5;bool left=false;bool right=false;int v=1;int blood=12;bool luo=false;int changePerson=0;} p1,p2;
class People
{
private:
    int x;
    int y;
    int width;
    int speed;
    bool left;
    bool right;
    int v;
    int blood;
    bool luo;
    int changePerson;
public:
    People();
    void setPeople(int,int);
    bool hasPeople();
    QRect mkRect();
    bool goLeft();
    bool goRight();
    void runLeft();
    void runRight();
    bool wheLuo();
    void changeChangePerson(char,int);
    int getChangePerson();
    int getX();
    void setX(int);
    int getY();
    void setY(int);
    void setLuo(bool);
    int getV();
    int getBottom();
    int getRight();
    void setBottom(int);
    void delBlood();
    void addBlood();
    void moveWithStairL();
    void moveWithStairR();
    int getBlood();
    void setMoveDirection(int);
    void stayStatic();
    ~People();
};

#endif // PEOPLE_H
