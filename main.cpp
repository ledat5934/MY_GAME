#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "game_image.h"
#include "maps.h"
#include "logic.h"
#include "character.h"
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
    images.load();
    graphic.prepareScene(images.background);
    game_map maps(images,graphic);
    maps.build_map();
    Mouse mouse(pile_size, SCREEN_HEIGHT-11*pile_size+12);
    characters charact(graphic,mouse,images);
    bool quit=false;
    graphic.renderTexture(images.character,mouse.x,mouse.y);
    graphic.presentScene();
    SDL_Event event;
    while(!quit)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        if(charact.check_move())
        {
            charact.charact_move();
            charact.present_scene();
            charact.update_status();
            charact.present_scene();
        }
    SDL_Delay(50);
    }
    waitUntilKeyPressed();
}
