#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "maps.h"
#include "game_image.h"
#include "trap.h"
#include "character.h"
struct Minimap
{
    int minimize=6;
    int mini_height=SCREEN_HEIGHT/minimize;
    int mini_width=map_width/minimize;
    SDL_Rect minimap;
    Graphics* graphic;
    Trap moved_spike;
    Character* character;
    Minimap(Graphics* _graphic, Character* _character)
    {
        graphic=_graphic;
        character=_character;
        minimap.h=mini_height;
        minimap.w=mini_width;
        minimap.x=SCREEN_WIDTH-mini_width-108;
        minimap.y=0;
        moved_spike.x=moved_spike.max_x=1008;
        moved_spike.min_x=18*pile_size;
        moved_spike.y=16*pile_size;
    }
    void draw_safe(int x,int y)
    {
        SDL_Rect rect;
        rect.h=rect.w=3;
        rect.x=minimap.x+x/minimize;
        rect.y=minimap.y+minimap.h-((SCREEN_HEIGHT-y)/minimize);
        SDL_SetRenderDrawColor(graphic->renderer,0,255,0,255);
        SDL_RenderFillRect(graphic->renderer,&rect);
    }
    void draw_character(int x,int y)
    {
        SDL_Rect rect;
        rect.h=rect.w=3;
        rect.x=minimap.x+x/minimize;
        rect.y=minimap.y+minimap.h-((SCREEN_HEIGHT-y)/minimize);
        SDL_SetRenderDrawColor(graphic->renderer,255,255,255,255);
        SDL_RenderFillRect(graphic->renderer,&rect);
    }
    void draw_danger(int x,int y)
    {
        SDL_Rect rect;
        rect.h=rect.w=3;
        rect.x=minimap.x+x/minimize;
        rect.y=minimap.y+minimap.h-((SCREEN_HEIGHT-y)/minimize);
        SDL_SetRenderDrawColor(graphic->renderer,255,0,0,255);
        SDL_RenderFillRect(graphic->renderer,&rect);
    }
    void draw_minimap()
    {
        SDL_SetRenderDrawColor(graphic->renderer,0,0,0,255);
        SDL_RenderFillRect(graphic->renderer,&minimap);
        for(auto &d:danger)
        {
            draw_danger(d.second,d.first);
        }
        for(auto &obj:can_stand)
        {
            draw_safe(obj.second,obj.first);
        }
        draw_danger(moved_spike.x,moved_spike.y);
        draw_character(character->x+character->cam,character->y);
    }
};

#endif // MINIMAP_H_INCLUDED