#ifndef TRAP_H_INCLUDED
#define TRAP_H_INCLUDED

struct Trap
{
    int x,y,min_x,max_x;
    int speed=2;
    Trap(){};
    Trap(int _x,int _y,int _min_x)
    {
        x=max_x=_x;
        min_x=_min_x;
        y=_y;
    }
    void update()
    {
        x += speed;
        if (x < min_x || x > max_x)
        {
            speed = -speed;
        }
    }
};

#endif // TRAP_H_INCLUDED
