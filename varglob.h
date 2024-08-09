#ifndef VARGLOB_H_INCLUDED
#define VARGLOB_H_INCLUDED

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;
SDL_Surface* screen = NULL;
SDL_Event evento;
const int fpeses = 60;
TTF_Font *font = NULL;
TTF_Font *fontbig = NULL;
SDL_Color text_color = {255, 255, 255};

#endif // VARGLOB_H_INCLUDED
