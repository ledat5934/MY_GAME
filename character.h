#ifndef _CHARACTER__H
#define _CHARACTER__H

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "maps.h"
#include "game_image.h"

struct Character{
    int x=pile_size;
    int y=SCREEN_HEIGHT-15*pile_size;
    int dy=velocity;
    int count_jump=0;
    bool move_left=false,move_right=false;
    int cam=0;
    int current_jump_high=0;
    Sprite *sprite; Graphics *graphic; Image *images;
    Character(Sprite *_sprite, Graphics *_graphic, Image *_images)
    {
        sprite=_sprite;graphic=_graphic;images=_images;
    }
    void present()
    {
        sprite->tick();
        SDL_RenderClear(graphic->renderer);
        graphic->prepareScene(images->background);
        for (auto &objects : v)
        {
            if (objects.x >= cam-18 && objects.x <= SCREEN_WIDTH + cam)
            {
                graphic->renderTexture(objects.texture, objects.x - cam, objects.y);
            }
        }
        Sprite* mySprite=sprite;
        graphic->render(x,y,*mySprite);
        graphic->presentScene();
    }
    bool check_can_stand()
    {
        pair<int,int> p={y+18,x-18+cam};
        auto it=can_stand.lower_bound(p);
        cout<<"x,y "<<x<<" "<<y<<endl;
        cout<<(*it).second<<" "<<(*it).first<<endl;
        if((*it).first==y+18)
        {
            if((*it).second-x-cam<18){return true;}
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
    void check_move()
    {
        if(check_can_stand())
        {
            count_jump=0;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_LEFT])
        {
            move_left=true;
            if(cam>0){move2();}
            else{move1();}
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT])
        {
            move_right=true;
            if(x>=SCREEN_WIDTH/2){move2();}
            else{move1();}
        }
        if (currentKeyStates[SDL_SCANCODE_UP])
        {
            if(count_jump==0)
            {
                dy-=6;
                count_jump=1;
            }
        }
        if(!check_can_stand()||dy<0)
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
