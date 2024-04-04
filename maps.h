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
};
vector<object>v;
struct game_map
{
    Image *images;
    Graphics *graphic;
    game_map(Image *_image, Graphics *_graphic)
    {
        images=_image;
        graphic=_graphic;
    }
    game_map(){};
    void add(SDL_Texture* tex,int i,int j)
    {
    graphic->renderTexture(tex,i,j);
    object o(tex,i,j);
    v.push_back(o);
    can_stand.insert({j,i});
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
        build_block(7*pile_size-2,14*pile_size-2,SCREEN_HEIGHT-7*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_inside,
images->ground_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
        build_block(40*pile_size-10,44*pile_size-10,SCREEN_HEIGHT-11*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
        build_block(32*pile_size-8,40*pile_size-8,SCREEN_HEIGHT-9*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_top,images->ground_inside,images->ground_inside,images->ground_right);
        build_block(24*pile_size-6,32*pile_size-6,SCREEN_HEIGHT-7*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_top,images->ground_inside,images->ground_inside,images->ground_right);
        build_block(14*pile_size-4,24*pile_size-4,SCREEN_HEIGHT-5*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_inside,
images->ground_top,images->ground_inside,images->ground_top,images->ground_top,images->ground_inside,images->ground_inside,images->ground_right);
    for(int i=SCREEN_HEIGHT-9*pile_size;i<=SCREEN_HEIGHT-pile_size;i+=pile_size)
       {
           add(images->waterfall,35.5*pile_size-6,i);
       }
    for(int i=SCREEN_HEIGHT-11*pile_size;i<=SCREEN_HEIGHT-pile_size;i+=pile_size)
       {
           add(images->waterfall,41.5*pile_size-10,i);
       }
    build_block(0,6*pile_size,SCREEN_HEIGHT-6*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_inside,
images->ground_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,
images->ground_right);
    build_block(25*pile_size-6,30*pile_size-6,SCREEN_HEIGHT-5*pile_size,SCREEN_HEIGHT,images->ground_inside,images->ground_left,
images->ground_left_top,images->ground_inside,images->ground_top,images->ground_right_top,images->ground_right,images->ground_inside,images->ground_right);
    build_block(0,map_width,SCREEN_HEIGHT-3*pile_size,SCREEN_HEIGHT,images->underwater,images->underwater,images->water,images->underwater,images->water,
                 images->water,images->underwater,images->underwater,images->underwater);
    add(images->arrow,2*pile_size,SCREEN_HEIGHT-10*pile_size);
    add(images->spike,5*pile_size,SCREEN_HEIGHT-10*pile_size);
    can_stand.erase(can_stand.find({SCREEN_HEIGHT-10*pile_size,2*pile_size}));

    }

};

#endif // _MAPS__H
