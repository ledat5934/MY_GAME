#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 594+18;
const char* WINDOW_TITLE = "Hello World!";
const int pile_size=18;
const int map_width=1008;
const int gravity=10;
const int char_frame[3][4] = {
    {  0, 0, 18, 18},
    { 21, 0, 18, 18},
    {42,0, 18, 18}};
const int frames = sizeof(char_frame)/sizeof(int)/4;
const int speed=3;
const int velocity=3;
const int jump_high=54;
#endif
