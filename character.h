#ifndef _CHARACTER__H
#define _CHARACTER__H
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "maps.h"
#include "game_image.h"
using namespace std;
void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)|| e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}
struct Character{
    int x=6;
    int y=432;
    int count_die=0;
    int dy=velocity;
    int level=1;
    int count_jump=0;
    bool move_left=false,move_right=false,move_up=false;
    int cam=0;
    bool pause_game=false;
    int jump_high=max_jump_high;
    bool real_map=false;
    int current_jump_high=0;
    bool can_move_right, can_move_left,can_stands;
    bool status_live=true;
    bool can_jump=true;
    int random_trap;
    Mix_Chunk* jump=Mix_LoadWAV("jump.wav");
    Graphics* graphic;
    Character(Graphics* _graphic){graphic=_graphic;}
    void check_move()
    {
        pair<int,int>p={y,x+cam-18};
        auto it1=can_stand.lower_bound(p);
        if((*it1).first<y+18&&(*it1).first>y-18)
        {
            auto it12=can_stand.lower_bound({(*it1).first,x+cam-18});
            if((*it12).second>=x+cam-18&&(*it12).second<=x+cam)
            {
                can_move_left=false;
            }
            else
            {
                can_move_left=true;
            }
        }
        else
        {
            can_move_left=true;
        }
        can_move_right=true;
        for(auto &obj:can_stand)
        {
            if(obj.first<y+18&&obj.first>y-18&&obj.second<=x+cam+18&&obj.second>=x+cam)
            {
                can_move_right=false;
            }
        }
        for(auto &p:can_stand)
        {
            if(y<=p.first+18&&y>=p.first&&x+cam>p.second-18&&x+cam<p.second+18)
            {
                move_up=false;
                dy=velocity;current_jump_high=0;
                break;
            }
        }
    }
    void check_can_stand()
    {
        can_stands=false;
        for(auto &ob:can_stand)
        {
            if(y+18>=ob.first&&y<=ob.first&&x+cam>ob.second-18&&x+cam<ob.second+18)
            {
                can_stands=true;
                y=ob.first-18;
                break;
            }
        }
    }
    void move1()
    {
        if(move_left==true){x-=speed;move_left=false;}
        if(move_right==true){x+=speed;move_right=false;}
    }
    void move2()
    {
        if(move_left==true)
        {
            cam-=speed;
            move_left=false;
        }
        if(move_right==true)
        {
            cam+=speed;
            move_right=false;
        }
    }
    void move()
    {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT])
        {
            move_left=true;
            if(can_move_left)
            {
                if(cam>0&&x<SCREEN_WIDTH/2){move2();}
                else{move1();}
            }
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT])
        {
            move_right=true;
            if(random_trap==0)
            {
                spike[0].first-=velocity;
            }
            if(can_move_right)
            {
                if(x<SCREEN_WIDTH/2||x+cam>=map_width-SCREEN_WIDTH/2)
                {
                    move1();
                }
                else
                {
                    move2();
                }
            }
        }
        if (currentKeyStates[SDL_SCANCODE_UP])
        {
            if(random_trap==1)
            {
                spike[0].second-=24;
                random_trap=2;
            }
            if(count_jump==0&&can_jump==true)
            {
                graphic->play_jump(jump);
                dy=-dy+1;
                count_jump=1;
                move_up=true;
            }
        }
        if(!can_stands||(dy<0&&move_up))
        {
            y+=dy;
            if(dy<0){current_jump_high-=dy;}
            if(current_jump_high>=jump_high)
            {
                current_jump_high=0;
                dy=velocity;
                jump_high=max_jump_high;
            }
        }
        if(currentKeyStates[SDL_SCANCODE_P])
        {
            pause_game=true;
        }
    }
};

#endif // _CHARACTER__H
