#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "game_image.h"
#include "maps.h"
using namespace std;
void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
int main(int argc,char**argv)
{
    Graphics graphic;
    graphic.init();
    Image images(graphic);
     game_map game_maps(images,graphic);
     game_maps.build_map();
     int cam=0;
     SDL_Event e;
     while(true)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if (e.type == SDL_QUIT) {
                graphic.quit();
                return 0;}
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        if(cam>=18){cam -= 18;
                        break;}
                    case SDLK_RIGHT:
                        if(cam<=map_width-SCREEN_WIDTH){cam += 18;
                        break;}
            }}
        }
        {SDL_RenderClear(graphic.renderer);
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
    }
    waitUntilKeyPressed();
}
