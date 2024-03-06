#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
using namespace std;
Graphics graphic;
const int map_width=1008;
SDL_Texture* tex;
SDL_Texture* tex122;
SDL_Texture* tex123;
SDL_Texture* tex022;
SDL_Texture* tex023;
void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
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
void add(SDL_Texture* tex,int i,int j)
{
    graphic.renderTexture(tex,i,j);
    object o(tex,i,j);
    v.push_back(o);
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
int main(int argc,char**argv)
{
    graphic.init();
     tex=graphic.loadTexture("tile_water.png");
     tex122=graphic.loadTexture("tile_0122.png");
     tex123=graphic.loadTexture("tile_0123.png");
     tex022=graphic.loadTexture("tile_0022.png");
     tex023=graphic.loadTexture("tile_0023.png");
     SDL_Texture* tile_u=graphic.loadTexture("tile_water.png");
     SDL_Texture* tile_w=graphic.loadTexture("tile_underwater.png");
     build_block(0,7*pile_size,SCREEN_HEIGHT-9*pile_size,SCREEN_HEIGHT,tex122,tex122,
tex022,tex122,tex022,tex023,tex123,tex122,tex123);
     build_block(7*pile_size-2,14*pile_size-2,SCREEN_HEIGHT-7*pile_size,SCREEN_HEIGHT,tex122,tex122,
tex022,tex122,tex022,tex023,tex123,tex122,tex123);
     build_block(14*pile_size-4,24*pile_size-4,SCREEN_HEIGHT-5*pile_size,SCREEN_HEIGHT,tex122,tex122,
tex022,tex122,tex022,tex023,tex123,tex122,tex123);
     build_block(24*pile_size-6,32*pile_size-6,SCREEN_HEIGHT-7*pile_size,SCREEN_HEIGHT,tex122,tex122,
tex022,tex122,tex022,tex023,tex123,tex122,tex123);
build_block(32*pile_size-8,40*pile_size-8,SCREEN_HEIGHT-9*pile_size,SCREEN_HEIGHT,tex122,tex122,
tex022,tex122,tex022,tex023,tex123,tex122,tex123);
build_block(40*pile_size-10,44*pile_size-10,SCREEN_HEIGHT-11*pile_size,SCREEN_HEIGHT,tex122,tex122,
tex022,tex122,tex022,tex023,tex123,tex122,tex123);
SDL_Texture* tex054=graphic.loadTexture("tile_0054.png");
for(int i=SCREEN_HEIGHT-9*pile_size;i<=SCREEN_HEIGHT-pile_size;i+=pile_size)
{
    add(tex054,35.5*pile_size-6,i);
}
for(int i=SCREEN_HEIGHT-11*pile_size;i<=SCREEN_HEIGHT-pile_size;i+=pile_size)
{
    add(tex054,41.5*pile_size-10,i);
}
     build_block(0,map_width,SCREEN_HEIGHT-3*pile_size,SCREEN_HEIGHT,tile_u,tile_u,tile_w,tile_u,tile_w,
                 tile_w,tile_u,tile_u,tile_u);


     int cam=0;
     SDL_Event e;
     while(true)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if (e.type == SDL_QUIT) {
                SDL_DestroyTexture(tex);
                graphic.quit();
                return 0;}
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        if(cam>=10){cam -= 10;
                        break;}
                    case SDLK_RIGHT:
                        if(cam<=map_width-SCREEN_WIDTH){cam += 10;
                        break;}}
            }
        }
        SDL_RenderClear(graphic.renderer);
        for(const object& o:v)
        {
            if(o.x<cam+SCREEN_WIDTH)
            {
                graphic.renderTexture(o.texture,o.x-cam,o.y);
            }
        }
    graphic.presentScene();
    SDL_Delay(100);
    }
    waitUntilKeyPressed();
}
