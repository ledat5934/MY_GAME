#ifndef _MAPS__H
#define _MAPS__H

#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "game_image.h"
using namespace std;

set<pair<int,int>>can_stand;
struct object
{
    SDL_Texture* texture;
    int x,y;
    object(SDL_Texture* tex1,int x1,int y1)
    {
        texture=tex1;x=x1;y=y1;
    }
//        bool operator==(const object& other)
//    {
//        return this->x == other.x && this->y == other.y ;
//    }
};
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
vector<object>v;
set<pair<int,int>>danger;
struct game_map
{
    Image *images;
    Graphics *graphic;
    int random;
    Trap moved_spike;
    game_map(Image *_image, Graphics *_graphic)
    {
        images=_image;
        graphic=_graphic;
        moved_spike.x=moved_spike.max_x=1008;
        moved_spike.min_x=18*pile_size;
        moved_spike.y=16*pile_size;
    }
    game_map(){};
    void add(SDL_Texture* tex,int i,int j)
    {
    graphic->renderTexture(tex,i,j);
    object o(tex,i,j);
    v.push_back(o);
    if(tex!=images->spike)
    {can_stand.insert({j,i});}
    if(tex==images->spike||tex==images->water)
    {
        danger.insert({j,i});
    }
    }
    void build_block(int x1,int x2,int y1,int y2,SDL_Texture* t1, SDL_Texture* t2, SDL_Texture* t3,SDL_Texture* t4,SDL_Texture* t5,SDL_Texture* t6,SDL_Texture* t7,SDL_Texture* t8,SDL_Texture* t9)
{
    add(t3,x1,y1);
    for(int i=y1+pile_size;i<=y2-2*pile_size;i+=pile_size)
    {
        add(t2,x1,i);
    }
    add(t4,x1,y2-pile_size);
    for(int i=x1+pile_size;i<=x2-2*pile_size;i+=pile_size)
    {
        add(t5,i,y1);
    }
    add(t6,x2-pile_size,y1);
    for(int i=y1+pile_size;i<=y2-2*pile_size;i+=pile_size)
    {
        add(t7,x2-pile_size,i);
    }
    add(t9,x2-pile_size,y2-pile_size);
    for(int i=x1+pile_size;i<=x2-2*pile_size;i+=pile_size)
    {
        add(t8,i,y2-pile_size);
    }
    for(int i=x1+pile_size;i<=x2-2*pile_size;i+=pile_size)
    {
        for(int j=y1+pile_size;j<=y2-2*pile_size;j+=pile_size)
        {
            add(t1,i,j);
        }
    }
}

    void build_map()
    {
        build_block(0,7*pile_size,SCREEN_HEIGHT-9*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_inside,
images->ground_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,
images->ground_right);
        build_block(7*pile_size,14*pile_size,SCREEN_HEIGHT-7*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_inside,
images->ground_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
        build_block(40*pile_size,48*pile_size,SCREEN_HEIGHT-11*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
        build_block(32*pile_size,40*pile_size,SCREEN_HEIGHT-9*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_top,images->ground_inside,images->ground_inside,images->ground_right);
        build_block(24*pile_size,32*pile_size,SCREEN_HEIGHT-7*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_top,images->ground_inside,images->ground_inside,images->ground_right);
    for(int i=SCREEN_HEIGHT-9*pile_size;i<=SCREEN_HEIGHT-pile_size;i+=pile_size)
       {
           add(images->waterfall,35*pile_size,i);
       }
    for(int i=SCREEN_HEIGHT-11*pile_size;i<=SCREEN_HEIGHT-pile_size;i+=pile_size)
       {
           add(images->waterfall,41*pile_size,i);
       }
    build_block(0,6*pile_size,SCREEN_HEIGHT-6*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_inside,
images->ground_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,
images->ground_right);
    build_block(25*pile_size,30*pile_size,SCREEN_HEIGHT-5*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
    build_block(0,map_width,SCREEN_HEIGHT-3*pile_size,SCREEN_HEIGHT,images->underwater,images->underwater,images->water,images->underwater,images->water,
                 images->water,images->underwater,images->underwater,images->underwater);
    add(images->arrow,2*pile_size,SCREEN_HEIGHT-10*pile_size);
    add(images->spike,5*pile_size,SCREEN_HEIGHT-10*pile_size);
    can_stand.erase(can_stand.find({SCREEN_HEIGHT-10*pile_size,2*pile_size}));
    add(images->ground_top,19*pile_size,27*pile_size);
    add(images->ground_top,21*pile_size,27*pile_size);
    add(images->ground_top,10*pile_size,25*pile_size);
    add(images->ground_top,12*pile_size,23*pile_size);
    add(images->ground_top,14*pile_size,21*pile_size);
    add(images->ground_top,16*pile_size,19*pile_size);
    add(images->cloud,20*pile_size,5*pile_size);
    add(images->cloud,29*pile_size,5*pile_size);
    add(images->cloud,40*pile_size,5*pile_size);
    for(int i=18*pile_size;i<=1008;i++)
    {
        add(images->ground_top,i,17*pile_size);
    }
    add(images->spike,468,468);
    add(images->ground_top,1008+4*pile_size,17*pile_size);
    add(images->ground_top,1008+5*pile_size,17*pile_size);
    add(images->spike,25*pile_size,16*pile_size);
    add(images->spike,36*pile_size,16*pile_size);
    srand(static_cast<unsigned>(time(0)));
    random= rand()%2;
    if(random==0)
    {
        random=15*pile_size;
        add(images->ground_top,17*pile_size,27*pile_size);
        add(images->ground_top,15*pile_size,27*pile_size);
    }
    else
    {
        random=17*pile_size;
        add(images->ground_top,15*pile_size,27*pile_size);
        add(images->ground_top,17*pile_size,27*pile_size);
    }
    cout<<random;
    }

};

#endif // _MAPS__H
