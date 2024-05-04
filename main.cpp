#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "game_image.h"
#include "maps.h"
#include "character.h"
#include "logic_game.h"
#include "minimap.h"
#include "menu.h"
using namespace std;
int main(int argc,char**argv)
{
    Graphics graphic;
    graphic.init();
    Image images(graphic);
    images.load();
    graphic.prepareScene(images.background);
    Sprite sprite;
    SDL_Texture* characterss=graphic.loadTexture("frame_char_.png");
    sprite.init(characterss,frames,char_frame);
    Character character(&graphic);
    game_menu menu(&images);
    Minimap mini(&graphic,&character);
    game_map maps(&images,&graphic,&mini);
    bool quit=false;
    logic_game logic(&character,&sprite,&maps,&menu);
    logic.do_logic();
    waitUntilKeyPressed();
}
