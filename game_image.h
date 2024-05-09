#ifndef _GAME_IMAGE__
#define _GAME_IMAGE__
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
struct Image
{
    Graphics graphics;
    Image(Graphics graphic)
    {
        graphics=graphic;
    }
    Image(){};
    SDL_Texture* ground_left_top;
    SDL_Texture* ground_top;
    SDL_Texture* ground_right_top;
    SDL_Texture* waterfall;
    SDL_Texture* ground_inside;
    SDL_Texture* ground_right;
    SDL_Texture* underwater;
    SDL_Texture* water;
    SDL_Texture* ground_left;
    SDL_Texture* arrow;
    SDL_Texture* spike;
    SDL_Texture* background;
    SDL_Texture* character;
    SDL_Texture* cloud;
    SDL_Texture* thunder;
    SDL_Texture* menu;
    SDL_Texture* sign;
    SDL_Texture* door;
    SDL_Texture* explosion_sprite;
    SDL_Texture* spring;
    SDL_Texture* spring2;
    void load()
    {
    ground_left_top=graphics.loadTexture("tile_0021.png");
    ground_top=graphics.loadTexture("tile_0022.png");
    ground_right_top=graphics.loadTexture("tile_0023.png");
    waterfall=graphics.loadTexture("tile_0054.png");
    ground_inside=graphics.loadTexture("tile_0122.png");
    ground_right=graphics.loadTexture("tile_0123.png");
    underwater=graphics.loadTexture("tile_water.png");
    water=graphics.loadTexture("tile_underwater.png");
    ground_left=graphics.loadTexture("tile_0121.png");
    arrow=graphics.loadTexture("tile_0088.png");
    spike=graphics.loadTexture("tile_0069.png");
    background=graphics.loadTexture("background2.png");
    character=graphics.loadTexture("char_01.png");
    cloud=graphics.loadTexture("cloud.png");
    thunder=graphics.loadTexture("thunder.png");
    menu=graphics.loadTexture("menu.png");
    sign=graphics.loadTexture("tile_0086.png");
    door=graphics.loadTexture("tile_0111.png");
    explosion_sprite=graphics.loadTexture("bomb.jpg");
    spring=graphics.loadTexture("tile_0108.png");
    spring2=graphics.loadTexture("tile_0107.png");
    }
};

#endif // _GAME_IMAGE__
