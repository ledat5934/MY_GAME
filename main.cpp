#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "game_image.h"
#include "maps.h"
#include "logic.h"
#include "character.h"
#include "do_logic.h"
using namespace std;
int main(int argc,char**argv)
{
    Graphics graphic;
    graphic.init();
    Image images(graphic);
    images.load();
    graphic.prepareScene(images.background);
    game_map maps(&images,&graphic);
    maps.build_map();
    Sprite sprite;
    SDL_Texture* characterss=graphic.loadTexture("frame_char_.png");
    sprite.init(characterss,frames,char_frame);
    Character character(&sprite, &maps);
    bool quit=false;
    graphic.render(character.x,character.y,sprite);
    graphic.presentScene();
    SDL_Event event;
    while(!quit)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        character.move();
    SDL_Delay(1);
    }
    waitUntilKeyPressed();
}
