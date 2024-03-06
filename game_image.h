#ifndef _GAME_IMAGE__
#define _GAME_IMAGE__
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"

struct Image
{
    Graphics graphics;
    SDL_Texture* ground_top;
    SDL_Texture* ground_right_top;
    SDL_Texture* waterfall;
    SDL_Texture* ground_inside;
    SDL_Texture* ground_right;
    SDL_Texture* underwater;
    SDL_Texture* water;
    Image(Graphics graphic)
    {
        graphics=graphic;
    }
    Image(){};
    void load_image()
    {
        ground_top=graphics.loadTexture("tile_0022.png");
        ground_right_top=graphics.loadTexture("tile_0023.png");
        waterfall=graphics.loadTexture("tile_0054.png");
        ground_inside=graphics.loadTexture("tile_0122.png");
        ground_right=graphics.loadTexture("tile_0123.png");
        underwater=graphics.loadTexture("water.png");
        water=graphics.loadTexture("underwater.png");
    }


};

#endif // _GAME_IMAGE__
