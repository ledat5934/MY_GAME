#ifndef LOGIC_GAME_H_INCLUDED
#define LOGIC_GAME_H_INCLUDED

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "maps.h"
#include "game_image.h"
#include "character.h"
#include "menu.h"
struct logic_game
{
    Character* character;
    Uint32 start_time;
    Sprite *sprite; Graphics *graphic; Image *images;game_map *maps;
    bool trap_started[3];
    bool trap_ended[3];
    int count_die=0;
    game_menu *menu;
    int vv=27*pile_size;
    TTF_Font* font;
    SDL_Color color = {0, 0, 0, 255};
    SDL_Texture* helloText;
    int random_number=0;
    bool is_playing=false;
    bool is_pausing=false;
    Mix_Music* background_music;
    Mix_Chunk* die;
    Uint32 game_start;
    vector<int>clouded={20*pile_size,29*pile_size,40*pile_size};
    logic_game(Character* _character,Sprite *_sprite, game_map *_maps,game_menu* _menu)
    {
        character=_character;
        sprite=_sprite;
        maps=_maps;
        menu=_menu;
        graphic=maps->graphic;
        images=maps->images;
        font=graphic->loadFont("Montserrat-VariableFont_wght.ttf", 15);
        memset(trap_started, false, sizeof(trap_started) );
        memset(trap_ended, false, sizeof(trap_ended));
        background_music=graphic->loadMusic("background_music.wav");
        game_start=SDL_GetTicks();
        graphic->play(background_music);
        die=Mix_LoadWAV("die.wav");
    }
    void present()
    {
        sprite->tick();
        SDL_RenderClear(graphic->renderer);
        graphic->prepareScene(images->background);
        maps->mini->draw_minimap();
        if(random_number<=2)
        {
            graphic->renderTexture(images->thunder,clouded[random_number]-character->cam+12,7*pile_size);
        }
        for (auto &objects:v)
        {
            if (objects.x >= character->cam-18 && objects.x <= SCREEN_WIDTH + character->cam)
            {
                graphic->renderTexture(objects.texture, objects.x - character->cam, objects.y);
            }
        }
        Sprite* mySprite=sprite;
        graphic->render(character->x,character->y,*mySprite);
        string death_count="DEATHS: "+to_string(count_die);
        helloText = graphic->renderText(death_count.c_str(), font, color);
        graphic->renderTexture(helloText, SCREEN_WIDTH-90, 10);
        graphic->renderTexture(images->spike,maps->moved_spike->x-character->cam,maps->moved_spike->y);
        graphic->presentScene();
    }
    bool check_danger()
	{
		for(auto &dangers:danger)
        {
            if(dangers.first>=character->y-18&&dangers.first<=character->y+18)
            {
                if(character->x+character->cam+18>=dangers.second&&character->x+character->cam<=dangers.second)
                {
                    return true;
                }
                if(character->x+character->cam<=dangers.second+18&&character->x+character->cam>=dangers.second)
                {
                    return true;
                }
            }
        }
        if(character->y>=maps->moved_spike->y-18&&character->y<=maps->moved_spike->y&&character->x+character->cam>=maps->moved_spike->x-18&&character->x+character->cam<=maps->moved_spike->x+18)
        {
            return true;
        }
        return false;
    }
    void fall()
    {
        character->can_stands=false;
        character->can_jump=false;
        character->can_move_left=character->can_move_right=false;
        character->y+=3;
    }
    void handle_dangerouse()
    {
        int time_caculate=SDL_GetTicks()-game_start;
        if(time_caculate%10==0){random_number=rand()%10;}
        if(check_danger())
        {
            character->status_live=false;
            return ;
        }
        if(random_number<=2)
        {
            if(character->x+character->cam>clouded[random_number]+12-pile_size&&character->y>=7*pile_size&&character->y<=20*pile_size&&character->x+character->cam<clouded[random_number]+12+pile_size)
            {
                character->status_live=false;
                present();
                return;
            }
        }
        if(character->x+character->cam==35*pile_size&&character->y>=SCREEN_HEIGHT-10*pile_size)
        {
            fall();
        }
        if(character->x+character->cam==738&&character->y>=396)
        {
            fall();
        }
        if(character->x+character->cam==630&&character->y>16*pile_size)
        {
            start_time=SDL_GetTicks();
            trap_started[0]=true;
        }
        if(character->x+character->cam>630&&trap_started[0]&&!trap_ended[0])
        {
            Uint32 current_time=SDL_GetTicks();
            double xx=(current_time-start_time)/12;
            if(xx>22){xx=22;trap_started[0]=false;trap_ended[0]=true;}
            maps->add(images->spike,702,432+22-xx);
            maps->add(images->ground_top,702,450);
            maps->add(images->ground_inside,702,468);
        }
        if(character->x+character->cam>=maps->random-18&&!trap_ended[1]&&character->y>23*pile_size)
        {
            trap_started[1]=true;
            trap_ended[1]=true;
            if(v.back().x==maps->random)
            {
                v.pop_back();
            }
            can_stand.erase(can_stand.find({27*pile_size,maps->random}));
        }
        if(character->x+character->cam>=1008&&character->y<=288)
        {
            trap_started[2]=true;
            maps->add(images->ground_top,1008+30*pile_size,17*pile_size);
            can_stand.erase(can_stand.find({17*pile_size,1008+30*pile_size}));
            maps->add(images->ground_top,1008+31*pile_size,17*pile_size);
            can_stand.erase(can_stand.find({17*pile_size,1008+31*pile_size}));
            start_time=SDL_GetTicks();
        }
        if(character->y>=SCREEN_HEIGHT)
        {
            character->status_live=false;
        }
        if(character->y==16*pile_size&&character->x+character->cam<=1008)
        {
            if(maps->moved_spike->x< character->x + character->cam &&maps->moved_spike->x>=maps->moved_spike->min_x&&maps->moved_spike->x<=maps->moved_spike->max_x)
                {maps->moved_spike->speed=abs(maps->moved_spike->speed);}
            else if(maps->moved_spike->x>=character-> x + character->cam&&maps->moved_spike->x>=maps->moved_spike->min_x&&maps->moved_spike->x<=maps->moved_spike->max_x)
            {
                maps->moved_spike->speed=-(abs(maps->moved_spike->speed));
            }
        }
    }
    void reset()
    {
        Mix_ResumeMusic();
        Mix_RewindMusic();
        is_playing=true;
        character->dy=velocity;
        character->status_live=true;
        count_die++;
        character->x=6;character->y=432;
        character->cam=0;
        v.clear();
        can_stand.clear();
        danger.clear();
        character->current_jump_high=0;
        maps->build_map();
        memset(trap_started,false,sizeof(trap_started));
        memset(trap_ended,false,sizeof(trap_ended));
    }
    void handle_die()
    {
        is_playing=false;
        Mix_PauseMusic();
        graphic->play_jump(die);
        waitUntilKeyPressed();
        reset();
    }
    void do_logic()
    {
        while(true)
        {
            while(SDL_PollEvent(&event))
            {
                if(menu->menu_is_playing)
                {
                    Mix_PauseMusic();
                    menu->menu_loop();
                }
                if(menu->menu_just_close)
                {
                    Mix_ResumeMusic();
                    Mix_RewindMusic();
                    menu->menu_just_close=false;
                    is_playing=true;
                    maps->build_map();
                }
                if(is_pausing)
                {
                    menu->pause_loop();
                }
            }
            if(is_playing)
            {
                cout<<character->x+character->cam<<" "<<character->y<<endl;
                maps->moved_spike->update();
                character->move_up=character->can_jump=true;
                character->check_move();
                handle_dangerouse();
                if(character->status_live==false)
                {
                    handle_die();
                    present();
                }
                character->check_can_stand();
                if(character->can_stands)
                {
                    character->count_jump=0;
                }
                else
                {
                    character->can_jump=false;
                }
                character->move();
                present();
            }
            if(character->pause_game)
            {
                is_playing=false;
                is_pausing=true;
                character->pause_game=false;
                menu->pause_option=0;
            }
            SDL_Delay(10);
        }
    }
};

#endif // LOGIC_GAME_H_INCLUDED
