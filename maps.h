#ifndef _MAPS__H
#define _MAPS__H

#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "game_image.h"
#include "minimap.h"
#include "trap.h"
using namespace std;
struct object
{
    SDL_Texture* texture;
    int x,y;
    object(SDL_Texture* tex1,int x1,int y1)
    {
        texture=tex1;x=x1;y=y1;
    }
};
vector<object>grounded;
struct game_map
{
    Image *images;
    Graphics *graphic;
    int random;
    Trap* moved_spike;
    Minimap *mini;
    game_map(Image *_image, Graphics *_graphic,Minimap *_mini)
    {
        images=_image;
        graphic=_graphic;
        mini=_mini;
        moved_spike=&mini->moved_spike;
    }
    game_map(){};
    void add(SDL_Texture* tex,int i,int j)
    {
        if(tex==images->spike)
        {
            graphic->renderTexture(tex,i,j);
            spike.push_back({i,j});
        }
        else
        {
            graphic->renderTexture(tex,i,j);
            object o(tex,i,j);
            grounded.push_back(o);
        }
        if(tex!=images->spike&&tex!=images->door&&tex!=images->sign&&tex!=images->water&&tex!=images->underwater)
            {can_stand.insert({j,i});}
        if(tex==images->spike||tex==images->water||tex==images->underwater)
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
        build_block(40*pile_size,58*pile_size,SCREEN_HEIGHT-11*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
        build_block(32*pile_size,40*pile_size,SCREEN_HEIGHT-9*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_top,images->ground_inside,images->ground_inside,images->ground_right);
        build_block(24*pile_size,32*pile_size,SCREEN_HEIGHT-7*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_top,images->ground_inside,images->ground_inside,images->ground_right);
        build_block(62*pile_size,68*pile_size,SCREEN_HEIGHT-11*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
        build_block(72*pile_size,78*pile_size,SCREEN_HEIGHT-11*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
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
    add(images->spike,5*pile_size,SCREEN_HEIGHT-10*pile_size);
    add(images->ground_top,19*pile_size,27*pile_size);
    add(images->ground_top,21*pile_size,27*pile_size);
    add(images->ground_top,10*pile_size,25*pile_size);
    add(images->ground_top,12*pile_size,23*pile_size);
    add(images->ground_top,14*pile_size,21*pile_size);
    add(images->ground_top,16*pile_size,19*pile_size);
    add(images->cloud,20*pile_size,5*pile_size);
    add(images->cloud,29*pile_size,5*pile_size);
    add(images->cloud,40*pile_size,5*pile_size);
    signs.push_back({{45,432},"Don't believe anything"});
    signs.push_back({{126,468},"Exit in the blue spot on the minimap"});
    signs.push_back({{1134,288},"You have find the real map! So intelligence !"});
    signs.push_back({{774,396},"Be careful with the underground bomb right next"});
    bomb.push_back({774+18,396});
    bomb.push_back({1098,288});
    signs.push_back({{852,396},"Be careful with the underground bomb right here"});
    bomb.push_back({852,396});
    add(images->spike,1116,396);
    signs.push_back({{1026,396},"Find life in death"});
    add(images->door,1386,396);
    for(int i=18*pile_size;i<=1008;i+=pile_size)
    {
        add(images->ground_top,i,17*pile_size);
    }
    for(int i=18*pile_size;i<map_width;i+=pile_size)
    {
        invisible_spike.push_back({i,18*pile_size});
    }
    add(images->spike,504,468);
    add(images->ground_top,1008+4*pile_size,17*pile_size);
    add(images->ground_top,1008+5*pile_size,17*pile_size);
    add(images->ground_top,1008+6*pile_size,17*pile_size);
    add(images->ground_top,1008+7*pile_size,17*pile_size);
    add(images->door,1098,288);
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
