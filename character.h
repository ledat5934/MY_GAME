#ifndef _CHARACTER__H
#define _CHARACTER__H
#include<bits/stdc++.h>
#include"defs.h"
#include<SDL.h>
#include<SDL_image.h>
#include "graphics.h"
#include "maps.h"
#include "game_image.h"
struct Mouse {
    int x, y;
    int dx = 0, dy = 0;
    int speed = 18;
    Mouse(int _x,int _y){x=_x;y=_y;}
    Mouse(){};
    void move() {
        x += dx; y += dy;
    }
    void turnNorth() {
        dy = -speed; dx = 0;
    }
    void turnSouth() {
        dy = speed; dx = 0;
    }
    void turnWest() {
        dy = 0; dx = -speed;
    }
    void turnEast() {
        dy = 0; dx = speed;
    }
};
struct characters
{
    Mouse mouse;
    Graphics graphic;
    Image images;
    characters(Graphics _graphic, Mouse _mouse,Image _images){graphic=_graphic;mouse=_mouse;images=_images;}
    characters(){};
    int cam=0;
    bool check_move()
    {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        bool arrowKeyPressed = (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_DOWN] ||
                             currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_RIGHT]);
        return arrowKeyPressed;
    }
    void charact_move()
    {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {if(cam>=18) cam-=18;}
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) { cam+=18;}
        else if(currentKeyStates[SDL_SCANCODE_UP]) {mouse.y-=54;}
        mouse.move();
    }
    void update_status()
    {
        while(mouse.y<=SCREEN_HEIGHT-11*pile_size+12){mouse.y+=3;present_scene();}
    }
    void present_scene()
    {
        SDL_RenderClear(graphic.renderer);
        graphic.prepareScene(images.background);
        for(auto &objects:v)
        {
            if(objects.x>=cam &&objects.x<=SCREEN_WIDTH+cam)
            {
                graphic.renderTexture(objects.texture,objects.x-cam,objects.y);
            }
        }
        graphic.renderTexture(images.character,mouse.x,mouse.y);
        graphic.presentScene();
    }
};
#endif // _CHARACTER__H



