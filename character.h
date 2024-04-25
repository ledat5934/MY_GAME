#ifndef _CHARACTER__H
#define _CHARACTER__H
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "defs.h"
#include "graphics.h"
#include "maps.h"
#include "game_image.h"
#include "save_point.h"
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
struct Character{
    int x=6;
    int y=432;
    int dy=velocity;
    int count_jump=0;
    bool move_left=false,move_right=false,move_up=false;
    int cam=0;
    int current_jump_high=0;
    bool can_move_right, can_move_left,can_stands;
    Uint32 start_time;
    Sprite *sprite; Graphics *graphic; Image *images;game_map *maps;
    bool status_live=true;
    bool can_jump=true;
    bool trap_started[3];
    bool trap_ended[3];
    int count_die=0;
    int vv=27*pile_size;
    TTF_Font* font;
    SDL_Color color = {0, 0, 0, 255};
    SDL_Texture* helloText;
    int random_number=0;
    Uint32 game_start;
    vector<int>clouded={20*pile_size,29*pile_size,40*pile_size};
//    SavePoint current_savepoint;
    Character(Sprite *_sprite, game_map *_maps)
    {
        sprite=_sprite;
        maps=_maps;
        graphic=maps->graphic;
        images=maps->images;
        font=graphic->loadFont("Montserrat-VariableFont_wght.ttf", 15);
        memset(trap_started, false, sizeof(trap_started) );
        memset(trap_ended, false, sizeof(trap_ended));
        game_start=SDL_GetTicks();
//        current_savepoint.x=6;
//        current_savepoint.y=432;
//        current_savepoint.maps=_maps;
    }
    void present()
    {
        sprite->tick();
        SDL_RenderClear(graphic->renderer);
        graphic->prepareScene(images->background);
        if(random_number<=2)
        {
            graphic->renderTexture(images->thunder,clouded[random_number]-cam+12,7*pile_size);
        }
        for (auto &objects:v)
        {
            if (objects.x >= cam-18 && objects.x <= SCREEN_WIDTH + cam)
            {
                graphic->renderTexture(objects.texture, objects.x - cam, objects.y);
            }
        }
        Sprite* mySprite=sprite;
        graphic->render(x,y,*mySprite);
        string death_count="DEATHS: "+to_string(count_die);
        helloText = graphic->renderText(death_count.c_str(), font, color);
        graphic->renderTexture(helloText, SCREEN_WIDTH-90, 10);
        graphic->renderTexture(images->spike,maps->moved_spike.x-cam,maps->moved_spike.y);
        graphic->presentScene();
    }
    void check_move()
    {
        pair<int,int>p={y,x+cam-18};
        auto it1=can_stand.lower_bound(p);
//        cout<<"x,cam,y" <<x<<" "<<cam<<" "<<y<<endl;
//        cout<<(*it1).second<<" "<<(*it1).first<<endl;
        if((*it1).first<y+18&&(*it1).first>y-18)
        {
            auto it12=can_stand.lower_bound({(*it1).first,x+cam-18});
//            cout<<(*it12).second<<" "<<(*it12).first<<endl;
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
        pair<int,int> p={y+18,x+cam-17};
        auto it=can_stand.lower_bound(p);
        if(it==can_stand.end()){can_stands=false;return;}
        if((*it).first==y+18)
        {
            if((*it).second-x-cam<18&&(*it).second>=x+cam-17)
                {
                    can_stands= true;
                    if(x+cam>738&&y<396)
                    {
//                        cout<<x+cam<<" "<<y<<endl;
//                        cout<<(*it).second<<" "<<(*it).first<<endl;
                    }
                    return;
                }
        }
        can_stands=false;
    }
    bool check_danger()
	{
		for(auto &dangers:danger)
        {
            if(dangers.first>=y-18&&dangers.first<=y+18)
            {
                if(x+cam+18>=dangers.second&&x+cam<=dangers.second)
                {
                    return true;
                }
                if(x+cam<=dangers.second+18&&x+cam>=dangers.second)
                {
                    return true;
                }
            }
        }
        if(y>=maps->moved_spike.y-18&&y<=maps->moved_spike.y&&x+cam>=maps->moved_spike.x-18&&x+cam<=maps->moved_spike.x+18)
        {
            return true;
        }
    return false;
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
    void handle_dangerouse()
    {
        cout<<x+cam<<" "<<y<<endl;
        int time_caculate=SDL_GetTicks()-game_start;
        if(time_caculate%10==0){random_number=rand()%10;}
        if(check_danger())
        {
            status_live=false;
            return ;
        }
        if(random_number<=2)
        {
            if(x+cam==clouded[random_number]+12&&y>=7*pile_size&&y<=20*pile_size)
            {
                status_live=false;
                return;
            }
        }
        if(x+cam==35*pile_size&&y>=SCREEN_HEIGHT-10*pile_size)
        {
            can_stands=false;
            can_jump=false;
            can_move_left=can_move_right=false;
            y+=3;
        }
        if(x+cam==738&&y>=396)
        {
            can_stands=false;
            can_jump=false;
            can_move_left=can_move_right=false;
            y+=3;
        }
        if(x+cam==630&&y>16*pile_size)
        {
            start_time=SDL_GetTicks();
            trap_started[0]=true;
        }
        if(x+cam>630&&trap_started[0]&&!trap_ended[0])
        {
            Uint32 current_time=SDL_GetTicks();
            double xx=(current_time-start_time)/12;
            if(xx>22){xx=22;trap_started[0]=false;trap_ended[0]=true;}
            maps->add(images->spike,702,432+22-xx);
            maps->add(images->ground_top,702,450);
            maps->add(images->ground_inside,702,468);
        }
        if(x+cam>=maps->random-18&&!trap_ended[1]&&y>23*pile_size)
        {
            trap_started[1]=true;
            trap_ended[1]=true;
            if(v.back().x==maps->random)
            {
                v.pop_back();
            }
            can_stand.erase(can_stand.find({27*pile_size,maps->random}));
        }
        if(x+cam>=1008&&y<=288)
        {
            trap_started[2]=true;
            maps->add(images->ground_top,1008+30*pile_size,17*pile_size);
            can_stand.erase(can_stand.find({17*pile_size,1008+30*pile_size}));
            maps->add(images->ground_top,1008+31*pile_size,17*pile_size);
            can_stand.erase(can_stand.find({17*pile_size,1008+31*pile_size}));
            start_time=SDL_GetTicks();
        }
        if(trap_started[2]==true)
        {

        }
        if(y>=SCREEN_HEIGHT)
        {
            status_live=false;
        }
        if(y==16*pile_size)
        {
            if(maps->moved_spike.x<x+cam&&maps->moved_spike.x>=maps->moved_spike.min_x&&maps->moved_spike.x<=maps->moved_spike.max_x)
                {maps->moved_spike.speed=abs(maps->moved_spike.speed);}
            else if(maps->moved_spike.x>=x+cam&&maps->moved_spike.x>=maps->moved_spike.min_x&&maps->moved_spike.x<=maps->moved_spike.max_x)
            {
                maps->moved_spike.speed=-(abs(maps->moved_spike.speed));
            }
        }
    }
    void move()
    {
        maps->moved_spike.update();
        move_up=can_jump=true;
        check_move();
        handle_dangerouse();
        if(status_live==false)
        {

            waitUntilKeyPressed();
            dy=velocity;
            status_live=true;
            count_die++;
            x=6;y=432;
            cam=0;
            v.clear();
            can_stand.clear();
            danger.clear();
            current_jump_high=0;
            maps->build_map();
            memset(trap_started,false,sizeof(trap_started));
            memset(trap_ended,false,sizeof(trap_ended));
        }
            check_can_stand();
            if(can_stands)
            {
                count_jump=0;
            }
            else
            {
                can_jump=false;
            }
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
                if(can_move_right)
                {
                    if(x<SCREEN_WIDTH/2)
                    {
                        move1();cout<<1;
                    }
                    else
                    {
                        move2();cout<<2;
                    }
                }
            }
            cout<<endl;
            if (currentKeyStates[SDL_SCANCODE_UP])
            {
                if(count_jump==0&&can_jump==true)
                {
                    dy-=6;
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
                }
            }
            present();

    }


};

#endif // _CHARACTER__H
