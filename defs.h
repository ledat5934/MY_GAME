#ifndef _DEFS__H
#define _DEFS__H

#include<bits/stdc++.h>
using namespace std;
const int SCREEN_WIDTH = 804;
const int SCREEN_HEIGHT = 594+18;
const char* WINDOW_TITLE = "Hello World!";
const int pile_size=18;
const int map_width=1008+18*30;
const int gravity=10;
set<pair<int,int>>can_stand;
set<pair<int,int>>danger;
SDL_Event event;
const int char_frame[3][4] = {
    {  0, 0, 18, 18},
    { 21, 0, 18, 18},
    {42,0, 18, 18}};
vector<pair<int,int>>top_score;
vector<pair<pair<int,int>,string>>signs;
vector<pair<int,int>> bomb;
vector<pair<int,int>>spike;
vector<pair<int,int>>invisible_spike;
const int frames = sizeof(char_frame)/sizeof(int)/4;
const int speed=3;
const int velocity=4;
const int max_jump_high=48;
const int start_x=pile_size;
const int start_y=SCREEN_HEIGHT-15*pile_size;
#endif
