#include <cstdlib>
#include <SDL.h>
#include <sdl_ttf.h>
#include <SDL_image.h>
#include <cstring>
#include <cstdio>
#include <sdl_mixer.h>
#include <iostream>
#include <math.h>
using namespace std;
#include "varglob.h"
#include "claseranking.h"
#include "claseobjeto.h"
#include "clasejugadorbrut.h"
#include "clasejugadorhard.h"
#include "claseenemigobrut.h"
#include "claseenemigograndebrut.h"
#include "claseenemigohard.h"
#include "claserocket.h"
#include "clasetimer.h"
#include "funciones.h"

int main ( int argc, char** argv )
{
    iniciarSDL();
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

    font = TTF_OpenFont("COPRGTB.ttf", 18);
    fontbig = TTF_OpenFont("COPRGTB.ttf", 48);
    srand(0);

    MENU();

    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_Quit();
    return 0;
}
