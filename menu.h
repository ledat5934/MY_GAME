#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "maps.h"
#include "game_image.h"
int mod(int a,int b)
{
    if(a<0)
    {
        return b-(b-a)%b;
    }
    return a%b;
}
struct game_menu
{
    Image* images;
    Graphics* graphic;
    SDL_Texture* menu;
    pair<int,int>options[3]={{202,211},{202,281},{202,351}};
    int option=0;
    TTF_Font* font;
    bool menu_is_playing=true;
    bool menu_just_close=false;
    SDL_Color color = {0, 0, 0, 255};
    SDL_Texture* high_score,*new_game,*continue_game;
    game_menu(Image* _images)
    {
        images=_images;
        graphic=&images->graphics;
        menu=images->menu;
        font=graphic->loadFont("Montserrat-VariableFont_wght.ttf", 30);
        high_score=graphic->renderText("HIGH SCORE",font,color);
        new_game=graphic->renderText("NEW GAME",font,color);
        continue_game=graphic->renderText("CONTINUE GAME",font,color);
    }
    void draw_option(int x,int y)
    {
        SDL_Rect rect;
        rect.w=400;
        rect.h=50;
        rect.x=x;
        rect.y=y;
        SDL_SetRenderDrawColor(graphic->renderer,171,183,171,255);
        SDL_RenderFillRect(graphic->renderer,&rect);
    }
    void draw_choose(int x,int y)
    {
        SDL_Rect rect;
        rect.w=400;
        rect.h=50;
        rect.x=x;
        rect.y=y;
        SDL_SetRenderDrawColor(graphic->renderer,44,127,200,255);
        SDL_RenderFillRect(graphic->renderer,&rect);
    }
    void render_text()
    {
        graphic->renderTexture(high_score,options[2].first,options[2].second+10);
        graphic->renderTexture(continue_game,options[0].first,options[0].second+10);
        graphic->renderTexture(new_game,options[1].first,options[1].second+10);
    }
    void present_menu()
    {
        graphic->prepareScene(images->menu);
        for(int i=0;i<3;i++)
        {
            draw_option(options[i].first,options[i].second);
        }
        draw_choose(options[option].first,options[option].second);
        render_text();
        graphic->presentScene();
    }
    void menu_loop()
    {
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_DOWN])
                {
                    option+=1;
                    option=mod(option,3);
                }
                else if (currentKeyStates[SDL_SCANCODE_UP])
                {
                    option-=1;
                    option=mod(option,3);
                }
                else if(currentKeyStates[SDL_SCANCODE_SPACE]&&option==1)
                {
                    menu_is_playing=false;
                    menu_just_close=true;
                }
                present_menu();
            }
};


#endif // MENU_H_INCLUDED
