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
    game_map maps(&images,&graphic);
    maps.build_map();
    cout<<can_stand.size()<<endl;
    Sprite sprite;
    SDL_Texture* characterss=graphic.loadTexture("frame_char_.png");
    sprite.init(characterss,frames,char_frame);
    Character character(&sprite, &graphic, &images);
    bool quit=false;
    graphic.render(character.x,character.y,sprite);
    graphic.presentScene();
    SDL_Event event;
    while(!quit)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        character.check_move();

    SDL_Delay(12);
    }
    waitUntilKeyPressed();
}
