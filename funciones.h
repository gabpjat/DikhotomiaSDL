#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void iniciarSDL() {
    SDL_Init( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE );
    SDL_WM_SetCaption( "Dikhotomia", NULL );
}

SDL_Surface* cargarImagen(const char direccion[50]) {
    SDL_Surface* imagen = NULL;
    SDL_Surface* optimizada = NULL;

    imagen = SDL_LoadBMP(direccion);
    if(imagen != NULL) {
        optimizada = SDL_DisplayFormat(imagen);
        SDL_FreeSurface(imagen);
    }

    if(optimizada == NULL) {
        cout << "fallo carga de imagen" << direccion << endl;
    }
    Uint32 colorkey = SDL_MapRGB(optimizada->format, 0, 0, 0);
    SDL_SetColorKey(optimizada, SDL_SRCCOLORKEY, colorkey);

    return optimizada;
}

void aplicarSuperficie(int x, int y, SDL_Surface* imagen, SDL_Surface* destino, SDL_Rect *clip = NULL) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(imagen, clip, destino, &offset);
}

bool checkpos(SDL_Rect& rect, int x, int y )
{
    if( ( x > rect.x ) && ( x < rect.x + rect.w ) && ( y > rect.y ) && ( y < rect.y + rect.h ) )
        {

            return true;
        }
    else
        {
            return false;
        }

    return true;
}

bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //Los lados del rectangulo
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calcular los lados del rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calcular los lados del rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //Si cualquiera de los lados de A estan fuera de los de B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //Si ninguno de los lados de A esta fuera de B
    return true;
}

void listar_records(SDL_Surface* fondo, const char direccion[50]) {
    SDL_Surface* nombre = NULL;
    SDL_Surface* puntos = NULL;
    SDL_Surface* kills = NULL;
    SDL_Surface* tiempo = NULL;
    SDL_Surface* mensaje = NULL;
    char score[7];
    char kyles[5];
    char time[8];


    FILE *P;
    P = fopen(direccion, "rb");
    if(P == NULL){
        exit(1996);
    }
    ranking lector, masp, mask, mast;
    while(fread(&lector, sizeof(ranking), 1, P)) {
        if(lector.get_puntaje() > masp.get_puntaje()) {
            masp = lector;
        }
        if(lector.get_muertes() > mask.get_muertes()) {
            mask = lector;
        }
        if(lector.get_segundos() > mast.get_segundos()) {
            mast = lector;
        }
    }
    fclose(P);

    aplicarSuperficie(0, 0, fondo, screen);

    mensaje = TTF_RenderText_Solid(font, "nombre                puntaje          muertes          segundos ", text_color);
    aplicarSuperficie(300, 150, mensaje, screen);
    SDL_FreeSurface(mensaje);

    itoa(masp.get_puntaje(), score, 10);
    itoa(masp.get_muertes(), kyles, 10);
    itoa(masp.get_segundos(), time, 10);

    mensaje = TTF_RenderText_Solid(font, "Mejor puntaje: ", text_color);
    nombre = TTF_RenderText_Solid(font, masp.get_nombre(), text_color);
    puntos = TTF_RenderText_Solid(font, score, text_color);
    kills = TTF_RenderText_Solid(font, kyles, text_color);
    tiempo = TTF_RenderText_Solid(font, time, text_color);

    aplicarSuperficie(100, 200, mensaje, screen);
    aplicarSuperficie(300, 200, nombre, screen);
    aplicarSuperficie(500, 200, puntos, screen);
    aplicarSuperficie(600, 200, kills, screen);
    aplicarSuperficie(700, 200, tiempo, screen);
    SDL_FreeSurface(mensaje);
    SDL_FreeSurface(nombre);
    SDL_FreeSurface(puntos);
    SDL_FreeSurface(kills);
    SDL_FreeSurface(tiempo);

    itoa(mask.get_puntaje(), score, 10);
    itoa(mask.get_muertes(), kyles, 10);
    itoa(mask.get_segundos(), time, 10);

    mensaje = TTF_RenderText_Solid(font, "Mas muertes: ", text_color);
    nombre = TTF_RenderText_Solid(font, mask.get_nombre(), text_color);
    puntos = TTF_RenderText_Solid(font, score, text_color);
    kills = TTF_RenderText_Solid(font, kyles, text_color);
    tiempo = TTF_RenderText_Solid(font, time, text_color);

    aplicarSuperficie(100, 300, mensaje, screen);
    aplicarSuperficie(300, 300, nombre, screen);
    aplicarSuperficie(500, 300, puntos, screen);
    aplicarSuperficie(600, 300, kills, screen);
    aplicarSuperficie(700, 300, tiempo, screen);
    SDL_FreeSurface(mensaje);
    SDL_FreeSurface(nombre);
    SDL_FreeSurface(puntos);
    SDL_FreeSurface(kills);
    SDL_FreeSurface(tiempo);

    itoa(mast.get_puntaje(), score, 10);
    itoa(mast.get_muertes(), kyles, 10);
    itoa(mast.get_segundos(), time, 10);

    mensaje = TTF_RenderText_Solid(font, "Mejor tiempo: ", text_color);
    nombre = TTF_RenderText_Solid(font, mast.get_nombre(), text_color);
    puntos = TTF_RenderText_Solid(font, score, text_color);
    kills = TTF_RenderText_Solid(font, kyles, text_color);
    tiempo = TTF_RenderText_Solid(font, time, text_color);

    aplicarSuperficie(100, 400, mensaje, screen);
    aplicarSuperficie(300, 400, nombre, screen);
    aplicarSuperficie(500, 400, puntos, screen);
    aplicarSuperficie(600, 400, kills, screen);
    aplicarSuperficie(700, 400, tiempo, screen);
    SDL_FreeSurface(mensaje);
    SDL_FreeSurface(nombre);
    SDL_FreeSurface(puntos);
    SDL_FreeSurface(kills);
    SDL_FreeSurface(tiempo);

    SDL_Flip(screen);

    int i = 1;
    while(i == 1) {
        while(SDL_PollEvent(&evento)) {
            if(evento.type == SDL_KEYDOWN) {
                switch(evento.key.keysym.sym) {
                case(SDLK_RETURN):
                    i = 0;
                    break;
                case(SDLK_ESCAPE):
                    i = 0;
                    break;
                case(SDLK_SPACE):
                    i = 0;
                    break;

                default:
                    break;
                }
            }
        }
    }


}

void BRUTEND(ranking rank, int segundos) {
    SDL_Surface* rankfondo = cargarImagen("graphics\\BRUT\\rankscreen.bmp");
    rank.set_segundos(segundos);
    rank.ingresar_nombre(rankfondo);
    rank.guardar("rankings\\BRUT.bin");
    listar_records(rankfondo, "rankings\\BRUT.bin");
    SDL_FreeSurface(rankfondo);
}

void HARDEND(ranking rank, int segundos) {
    SDL_Surface* rankfondo = cargarImagen("graphics\\HARD\\fondoded.bmp");
    rank.set_segundos(segundos);
    rank.ingresar_nombre(rankfondo);
    rank.guardar("rankings\\HARD.bin");
    listar_records(rankfondo, "rankings\\HARD.bin");
    SDL_FreeSurface(rankfondo);
}

void BRUT() {
    ///Se abren todos los graficos necesarios:
    SDL_Surface* fondo = cargarImagen("graphics\\BRUT\\levelback.bmp");
    SDL_Surface* frente = cargarImagen("graphics\\BRUT\\levelfront.bmp");
    SDL_Surface* kurtsheet = cargarImagen("graphics\\BRUT\\fullspritesheetkurt.bmp");
    SDL_Surface* enemigochico = cargarImagen("graphics\\BRUT\\enemynormal.bmp");
    SDL_Surface* HUD = cargarImagen("graphics\\BRUT\\UI.bmp");
    SDL_Surface* pillsprite = cargarImagen("graphics\\BRUT\\pills.bmp");
    SDL_Surface* enemigogrande = cargarImagen("graphics\\BRUT\\enemybig.bmp");
    SDL_Surface* mensaje = NULL;
    SDL_Surface* vida = NULL;
    SDL_Surface* cronometro = NULL;
    SDL_Surface* puntos = NULL;
    SDL_Surface* muertes = NULL;
    SDL_Surface* multiplicador = NULL;

    ///Se abren todos los archivos de audio necesarios:
    Mix_Music *seek300 = Mix_LoadMUS("audio\\brut\\seek300.wav"); ///musica de fondo
    Mix_Chunk *death = Mix_LoadWAV("audio\\brut\\death.wav"); ///musica al morir
    Mix_Chunk *bigdeath = Mix_LoadWAV("audio\\brut\\bigdeath.wav"); ///grande muere
    Mix_Chunk *smalldeath = Mix_LoadWAV("audio\\brut\\smalldeath.wav"); ///chico muere
    Mix_Chunk *dash = Mix_LoadWAV("audio\\brut\\dash.wav"); ///dash
    Mix_Chunk *kickhit = Mix_LoadWAV("audio\\brut\\kickhit.wav"); ///pegar patada
    Mix_Chunk *enemy_fall = Mix_LoadWAV("audio\\brut\\enemy_fall.wav"); ///enemigo termina de caer al suelo
    Mix_Chunk *impact = Mix_LoadWAV("audio\\brut\\impact.wav"); ///enemigo en el aire se choca con un enemigo chico
    Mix_Chunk *impactbig = Mix_LoadWAV("audio\\brut\\impactbig.wav"); ///enemigo en el aire se choca con un enemigo grande
    Mix_Chunk *bigpunch = Mix_LoadWAV("audio\\brut\\bigpunch.wav"); ///recibir golpe de enemigo grande
    Mix_Chunk *smallpunch = Mix_LoadWAV("audio\\brut\\smallpunch.wav"); ///recibir golpe de enemigo chico
    Mix_Chunk *getpills = Mix_LoadWAV("audio\\brut\\getpills.wav"); ///conseguir pastillas

    jugadorkurt kurt;
    enemigobrut small[20];
    enemigograndebrut big[4];
    pastillas pills;

    int i, offsetx, offsety, segundos, ciclo_spawn, ciclo_spawn_grandes;

    kurt.set_width(96);
    kurt.set_height(96);
    kurt.set_posx(420);
    kurt.set_posy(240);
    kurt.set_hitboxh(96-40);
    kurt.set_hitboxw(96-78);

    for(i=0; i<20; i++) {
        small[i].set_width(96);
        small[i].set_height(96);
        small[i].set_posx(-100);
        small[i].set_posy(0);
    }

    for(i=0; i<4; i++) {
        big[i].set_width(96);
        big[i].set_height(96);
        big[i].set_posx(1000);
        big[i].set_posy(-200);
    }

    SDL_Rect kurtclip[24]; ///spritesheet para kurt
    SDL_Rect enemigoclip[12]; ///spritesheet para los enemigos chicos
    SDL_Rect pillsclip[3]; ///spritesheet para las pastillas
    SDL_Rect enemigograndeclip[10]; ///spritesheet para los enemigos grandes

    ///asignacion de cada posicion de las spritesheets:

    offsetx = offsety = segundos = ciclo_spawn = ciclo_spawn_grandes = 0;
    for(i=0; i<24; i++) {
        if(offsety == 96*6) {
            offsety = 0;
        }
        if(offsetx == 96*4) {
            offsetx = 0;
            offsety += 96;
        }
            kurtclip[i].h = 96;
            kurtclip[i].w = 96;
            kurtclip[i].x = offsetx;
            kurtclip[i].y = offsety;
            offsetx += 96;

    }
    offsety = 0;
    for(i=0; i<12; i++) {
        enemigoclip[i].h = 96;
        enemigoclip[i].w = 96;
        enemigoclip[i].x = 0;
        enemigoclip[i].y = offsety;
        offsety += 96;
    }

    offsety = 0;
    for(i=0; i<10; i++) {
        enemigograndeclip[i].h = 96;
        enemigograndeclip[i].w = 96;
        enemigograndeclip[i].x = 0;
        enemigograndeclip[i].y = offsety;
        offsety += 96;
    }

    offsety = 0;
    for(i=0; i<3; i++) {
        pillsclip[i].h = 48;
        pillsclip[i].w = 48;
        pillsclip[i].x = 0;
        pillsclip[i].y = offsety;
        offsety += 48;
    }

    ///variables importantes:
    bool fin = false;
    int frame = 0;
    timer fps;
    char tiempo[5];
    char charvida[3];
    char puntaje[8];
    char kills[5];
    char mult[3];
    int countdown = 10;
    int muertesrecientes = 0;
    int multiplier = 1; ///multiplicador de puntaje, cuanto más alto, más dificil el juego! (sin implementar)
    ranking rank;
    Mix_PlayMusic(seek300, -1);

    ///inicio del ciclo:////////////////////////////////////////////////////////////////////////////////////////////////////
    while(fin == false) {

        ///Todas las cosas relacionadas al framerate:
        fps.start();

        frame++;

        if (frame == fpeses) {
            frame = 0;
            segundos++;
            ciclo_spawn++;
            ciclo_spawn_grandes++;
            if(multiplier > 1) {
                countdown--;
                if(countdown < 1) {
                    multiplier = 1;
                    muertesrecientes = 0;
                }
            }
        }

        ///Todo lo relacionado al input:
        while(SDL_PollEvent(&evento)) {

            if(evento.type == SDL_QUIT) fin = true;

            if(evento.type == SDL_KEYDOWN) {
                kurt.movimiento();
                if(evento.key.keysym.sym == SDLK_ESCAPE) {
                    fin = true;
                }
            }

            else if( evento.type == SDL_KEYUP ){
                kurt.frenar();
            }
        }

        ///PASTILLAS --------------

        if(pills.get_cooldown() > 0) {
            pills.set_cooldown(pills.get_cooldown() - 1);
        }

        if((pills.get_cooldown() == 0) && (pills.get_estado() == 0)) {
            pills.set_estado(2);
        }

        if((segundos > 0) && (segundos % 20 == 0) && (pills.get_estado() == 2)) {
            pills.spawn_brut();
        }

        if(pills.get_estado() == 1) {
            if (check_collision(kurt.get_hitbox(), pills.get_pickbox())) {
                Mix_PlayChannel(-1, getpills, 0);
                kurt.set_salud(kurt.get_salud() + 1);
                pills.despawn();
            }
        }

        ///------------------------

        ///Funciones de movimiento:
        kurt.mover();

        if(kurt.get_estado() == 3 && kurt.get_framecont() == 0) {
            Mix_PlayChannel(-1, dash, 0);
        }

        if(kurt.get_cooldown() > 0) {
            kurt.set_cooldown((kurt.get_cooldown()) - 1);
        }

        i = 0;
        while(i < 20) {
            if(check_collision(kurt.get_grabbox(), small[i].get_hitbox()) && small[i].get_estado() == 3 && kurt.get_estado() == 4) {
                small[i].set_framecont(0);
                small[i].set_estado(4);
                kurt.set_framecont(0);
                kurt.set_estado(5);
                i = 20;
            }
            i++;
        }

        for(i=0; i<20; i++) { ///actividades de enemigos chicos
            if(small[i].get_activo() == true) {
                if(small[i].get_cooldown() > 0) {
                    small[i].set_cooldown(small[i].get_cooldown()-1);
                }

                if(check_collision(kurt.get_kickbox(), small[i].get_hitbox()) && kurt.get_estado() == 2) {
                    Mix_PlayChannel(-1, kickhit, 0);
                    small[i].set_framecont(0);
                    small[i].set_estado(3);
                }

                if(check_collision(kurt.get_hitbox(), small[i].get_punchbox()) && small[i].get_estado() < 3 && small[i].get_cooldown() == 0) {
                    Mix_PlayChannel(-1, smallpunch, 0);
                    SDL_Delay(100);
                    kurt.set_framecont(0);
                    kurt.set_estado(6);
                    small[i].set_framecont(0);
                    small[i].set_estado(5);
                    kurt.set_salud(kurt.get_salud()-1);
                }

                if(small[i].get_estado() == 4) {
                    for(offsetx=0; offsetx<20; offsetx++) {
                        if(offsetx != i){
                            if(check_collision(small[i].get_throwbox(), small[offsetx].get_hitbox())) {
                                if(small[offsetx].get_estado() != 3) {
                                    Mix_PlayChannel(-1, impact, 0);
                                    SDL_Delay(40);
                                    small[offsetx].set_salud(small[offsetx].get_salud() - 1);
                                }
                                small[offsetx].set_estado(3);
                                small[offsetx].set_framecont(0);
                            }
                        }
                    }
                    for(offsetx=0; offsetx<4; offsetx++) {
                        if(check_collision(small[i].get_throwbox(), big[offsetx].get_hitbox())) {
                            if(big[offsetx].get_estado() != 3) {
                                Mix_PlayChannel(-1, impactbig, 0);
                                SDL_Delay(40);
                                big[offsetx].set_salud(big[offsetx].get_salud() - 1);
                                big[offsetx].set_estado(3);
                                big[offsetx].set_framecont(0);
                            }

                        }
                    }
                }



                small[i].accion(kurt.get_posx(), kurt.get_posy(), kurt.get_orientacion());

                small[i].mover();

                if(small[i].get_estado() == 4 && small[i].get_framecont() == 60) {
                    Mix_PlayChannel(-1, enemy_fall, 0);
                }

                if(small[i].get_salud() == 0) {
                    Mix_PlayChannel(-1, smalldeath, 0);
                    rank.set_puntaje(rank.get_puntaje()+(100*multiplier));
                    rank.set_muertes(rank.get_muertes()+1);
                    muertesrecientes++;
                    small[i].set_posx(-100);
                    small[i].set_posy(30);
                    small[i].set_punchx(1000);
                    small[i].set_punchy(600);
                    small[i].set_activo(false);
                }
            }
        }

        for(i=0; i<4; i++) { ///actividades de enemigos grandes
            if(big[i].get_activo() == true) {
                if(big[i].get_cooldown() > 0) {
                    big[i].set_cooldown(big[i].get_cooldown()-1);
                }

                if(check_collision(kurt.get_hitbox(), big[i].get_punchbox()) && big[i].get_estado() < 3 && big[i].get_cooldown() == 0) {
                    Mix_PlayChannel(-1, bigpunch, 0);
                    SDL_Delay(100);
                    kurt.set_framecont(0);
                    kurt.set_estado(6);
                    big[i].set_framecont(0);
                    big[i].set_estado(5);
                    kurt.set_salud(kurt.get_salud()-2);
                }

                big[i].accion(kurt.get_posx(), kurt.get_posy(), kurt.get_orientacion());

                big[i].mover();

                if(big[i].get_salud() == 0) {
                    Mix_PlayChannel(-1, bigdeath, 0);
                    rank.set_puntaje(rank.get_puntaje()+(300*multiplier));
                    rank.set_muertes(rank.get_muertes()+1);
                    muertesrecientes+=2;
                    big[i].set_posx(1000);
                    big[i].set_posy(600);
                    big[i].set_punchx(1000);
                    big[i].set_punchy(600);
                    big[i].set_activo(false);
                }
            }
        }

        ///Spawn de enemigos:
        if(ciclo_spawn >= 2) {
            ciclo_spawn = 0;
            i = 0;
            while(i<20) {
                if(small[i].get_activo() == false){
                    small[i].set_activo(true);
                    small[i].set_salud(2);
                    small[i].spawn();
                    i=20;
                }
                i++;
            }
        }

        if(ciclo_spawn_grandes >= 8) {
            ciclo_spawn_grandes = 0;
            i = 0;
            while(i<4) {
                if(big[i].get_activo() == false){
                    big[i].set_activo(true);
                    big[i].spawn();
                    i=20;
                }
                i++;
            }
        }

        ///Multiplicador de puntaje:

        if(muertesrecientes > 10 && multiplier == 1) {
            multiplier++;
            countdown = 15;
            muertesrecientes = 0;
        }
        else if(muertesrecientes > 15 && multiplier == 2) {
            multiplier++;
            countdown = 10;
            muertesrecientes = 0;
        }

        if(kurt.get_salud() < 1) {
            fin = true;
            Mix_HaltMusic();
            if(Mix_PlayChannel(-1, death, 0) == -1) {
                exit(-32);
            }
            mensaje = TTF_RenderText_Solid(fontbig, "B R U T A L I Z E D" ,text_color);
        }

        itoa(segundos, tiempo, 10);
        cronometro = TTF_RenderText_Solid(font, tiempo, text_color);
        itoa(kurt.get_salud(), charvida, 10);
        vida = TTF_RenderText_Solid(font, charvida, text_color);
        itoa(rank.get_puntaje(), puntaje, 10);
        puntos = TTF_RenderText_Solid(font, puntaje, text_color);
        itoa(rank.get_muertes(), kills, 10);
        muertes = TTF_RenderText_Solid(font, kills, text_color);
        itoa(multiplier, mult, 10);
        multiplicador = TTF_RenderText_Solid(fontbig, mult, text_color);

        aplicarSuperficie(0, 0, fondo, screen);
        for(i=0; i<4; i++) {
            aplicarSuperficie(big[i].get_posx(), big[i].get_posy(), enemigogrande, screen, &enemigograndeclip[big[i].definir_frame(frame)]);
        }
        for(i=0; i<20; i++) {
            aplicarSuperficie(small[i].get_posx(), small[i].get_posy(), enemigochico, screen, &enemigoclip[small[i].definir_frame(frame)]);
        }
        aplicarSuperficie(pills.get_posx(), pills.get_posy(), pillsprite, screen, &pillsclip[pills.animar_brut(frame)]);
        aplicarSuperficie(kurt.get_posx(), kurt.get_posy(), kurtsheet, screen, &kurtclip[kurt.definir_frame(frame)]);
        aplicarSuperficie(0, 0, frente, screen);
        aplicarSuperficie(0, 0, HUD, screen);
        aplicarSuperficie(120, 498, vida, screen);
        aplicarSuperficie(850, 498, cronometro, screen);
        aplicarSuperficie(320, 498, puntos, screen);
        aplicarSuperficie(600, 498, muertes, screen);
        aplicarSuperficie(880, 20, multiplicador, screen);
        aplicarSuperficie(260, 250, mensaje, screen);
        SDL_Flip(screen);

        SDL_FreeSurface(cronometro);
        SDL_FreeSurface(vida);
        SDL_FreeSurface(puntos);
        SDL_FreeSurface(multiplicador);
        SDL_FreeSurface(muertes);
        SDL_FreeSurface(mensaje);

        if(kurt.get_salud() < 1) {
            SDL_Delay(3000);
            BRUTEND(rank, segundos);
        }

        if((fps.get_ticks() < 1000 / fpeses))
        {
            SDL_Delay((1000 / fpeses) - fps.get_ticks());
        }
    }
    ///Fin del ciclo//////////////////////////////////////////////////////

    ///Se liberan todos los graficos
    SDL_FreeSurface(pillsprite);
    SDL_FreeSurface(HUD);
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(frente);
    SDL_FreeSurface(kurtsheet);
    SDL_FreeSurface(enemigochico);
    SDL_FreeSurface(enemigogrande);
    ///Se libera todo el audio
    if(Mix_PlayingMusic() != 0){
        Mix_HaltMusic();
    }
    Mix_FreeMusic(seek300);
    Mix_FreeChunk(death);
    Mix_FreeChunk(bigdeath);
    Mix_FreeChunk(smalldeath);
    Mix_FreeChunk(dash);
    Mix_FreeChunk(kickhit);
    Mix_FreeChunk(enemy_fall);
    Mix_FreeChunk(impact);
    Mix_FreeChunk(impactbig);
    Mix_FreeChunk(bigpunch);
    Mix_FreeChunk(smallpunch);
    Mix_FreeChunk(getpills);
}




void HARD() {
    ///Se abren todos los graficos necesarios:
    SDL_Surface* fondo = cargarImagen("graphics\\HARD\\fondo3.bmp");
    SDL_Surface* johnsheet = cargarImagen("graphics\\HARD\\JohnSpritesheet.bmp");
    SDL_Surface* enemigochico = cargarImagen("graphics\\HARD\\enemyhardnormalnew.bmp");
    SDL_Surface* enemigogrande = cargarImagen("graphics\\HARD\\enemyhardbig.bmp");
    SDL_Surface* enemigoblip = cargarImagen("graphics\\HARD\\kamikazeblipp.bmp");
    SDL_Surface* rocketimg = cargarImagen("graphics\\HARD\\rocketspritesheet.bmp");
    SDL_Surface* explosionimg = cargarImagen("graphics\\HARD\\explosion.bmp");
    SDL_Surface* blipexplosion = cargarImagen("graphics\\HARD\\blipexplosion.bmp");
    SDL_Surface* HUD = cargarImagen("graphics\\HARD\\UI.bmp");
    SDL_Surface* cursor = cargarImagen("graphics\\HARD\\crosshair.bmp");
    SDL_Surface* botiquin = cargarImagen("graphics\\HARD\\pills.bmp");
    SDL_Surface* mensaje = NULL;
    SDL_Surface* vida = NULL;
    SDL_Surface* cronometro = NULL;
    SDL_Surface* puntos = NULL;
    SDL_Surface* muertes = NULL;
    SDL_Surface* multiplicador = NULL;

    ///Se abren todos los archivos de audio necesarios:
    Mix_Music *theme = Mix_LoadMUS("audio\\hard\\CrystalProtocol.wav"); ///musica de fondo
    Mix_Chunk *rocketshoot = Mix_LoadWAV("audio\\hard\\rocket.wav"); ///disparo
    Mix_Chunk *jump = Mix_LoadWAV("audio\\hard\\jump.wav"); ///salto
    Mix_Chunk *smalldeath = Mix_LoadWAV("audio\\hard\\smalldeath.wav"); ///chico muere
    Mix_Chunk *dash = Mix_LoadWAV("audio\\hard\\dash.wav"); ///dash

    Rocket rocket[3];
    SDL_Rect explosion[3];

    int i, offsetx, offsety, segundos, ciclo_spawn, ciclo_spawn_grandes, ciclo_spawn_blips;
    int cantGluttons = 5;
    int cantMagnatrons = 2;
    int cantBlips = 1;
    int flagpuntaje = 0;

    for(i=0; i<3; i++) {
        explosion[i].x = 600;
        explosion[i].y = 1500;
        explosion[i].w=30;
        explosion[i].h=30;
    }

    SDL_Rect floor;
    floor.x = -100;
    floor.y = 496;
    floor.w = SCREEN_WIDTH+200;
    floor.h = 100; ///joy

    jugadorhard john;

    enemigohard vGluttons[25];
    enemigograndehard vMagnatrons[10];
    enemigobliphard vBlip[5];
    blipexplosionhard vExp[5];

    pastillas medpack;

    john.set_width(96);
    john.set_height(96);
    john.set_posx(300);
    john.set_posy(400);
    john.set_hitboxh(96-20);
    john.set_hitboxw(96-78);

    for(i=0; i<25; i++) {
        vGluttons[i].set_width(96);
        vGluttons[i].set_height(96);
        vGluttons[i].set_posx(-100);
        vGluttons[i].set_posy(0);
    }

    for(i=0; i<10; i++)
    {
        vMagnatrons[i].set_width(96);
        vMagnatrons[i].set_height(96);
        vMagnatrons[i].set_posx(-200);
        vMagnatrons[i].set_posy(-500);
    }

    SDL_Rect johnclip[42]; ///spritesheet para JOHN
    SDL_Rect enemigoclip[14]; ///spritesheet para los enemigos chicos
    SDL_Rect enemigograndeclip[14]; ///spritesheet para los enemigos grandes
    SDL_Rect enemigoblipclip[6]; ///spritesheet para los enemigos voladores
    SDL_Rect rocketclip[8]; ///spritesheet para misiles
    SDL_Rect botiquinclip[8]; ///para el botiquin

    ///asignacion de cada posicion de las spritesheets:

    offsetx = offsety = segundos = ciclo_spawn = 0;
    for(i=0; i<42; i++) {
        if(offsety == 96*14) ///filas
        {
            offsety = 0;
        }
        if(offsetx == 96*3) ///columnas
        {
            offsetx = 0;
            offsety += 96;
        }
            johnclip[i].h = 96;
            johnclip[i].w = 96;
            johnclip[i].x = offsetx;
            johnclip[i].y = offsety;
            offsetx += 96;

    }
    offsety = 0;
    for(i=0; i<14; i++) {
        enemigoclip[i].h = 96;
        enemigoclip[i].w = 96;
        enemigoclip[i].x = 0;
        enemigoclip[i].y = offsety;
        offsety += 96;
    }
    offsety = 0;
    for(i=0; i<14; i++)
    {
        enemigograndeclip[i].h = 96;
        enemigograndeclip[i].w = 96;
        enemigograndeclip[i].x = 0;
        enemigograndeclip[i].y = offsety;
        offsety += 96;
    }
    offsety = 0;
    for(i=0;i<6; i++)
    {
        enemigoblipclip[i].h=96;
        enemigoblipclip[i].w=96;
        enemigoblipclip[i].x=0;
        enemigoblipclip[i].y=offsety;
        offsety+= 96;
    }

    offsety = 0;
    for(i=0; i<8; i++)
    {
        rocketclip[i].h= 15;
        rocketclip[i].w= 15;
        rocketclip[i].x= 0;
        rocketclip[i].y= offsety;
        offsety += 15;
    }
    offsety = 0;
    for(i=0; i<8; i++)
    {
        botiquinclip[i].h= 48;
        botiquinclip[i].w= 48;
        botiquinclip[i].x= 0;
        botiquinclip[i].y= offsety;
        offsety += 48;
    }



    ///variables importantes:
    bool fin = false;
    bool spawner = true;
    bool freeze = false;
    int frame = 0;
    timer fps;
    char tiempo[5];
    char charvida[3];
    int contexp[3] = {0, 0, 0};
    float ultmousex = -50;
    float ultmousey = -50;
    char puntaje[8];
    char kills[5];
    char mult[3];
    int countdown = 5;
    int muertesrecientes = 0;
    int multiplier = 1;
    ciclo_spawn = 0;
    ciclo_spawn_grandes = 0;
    ciclo_spawn_blips = 0;
    john.set_salud(5);
    john.set_shoot_cooldown(0);
    ranking rank;
    Mix_PlayMusic(theme, -1);

    SDL_ShowCursor(SDL_DISABLE);

    ///inicio del ciclo://////////////////////////////////////////////////////
    while(fin == false) {

        ///Todas las cosas relacionadas al framerate:
        fps.start();

        frame++;

        if (frame == fpeses) {
            frame = 0;
            segundos++;
            ciclo_spawn++;
            ciclo_spawn_grandes++;
            ciclo_spawn_blips++;

            if(multiplier > 1) {
                countdown--;
                if(countdown < 1) {
                    multiplier = 1;
                    muertesrecientes = 0;
                }
            }
        }


        if(john.get_shoot_cooldown() > 0) {
            john.set_shoot_cooldown(john.get_shoot_cooldown()-1);
        }

        ///Todo lo relacionado al input:
        while(SDL_PollEvent(&evento)) {

            if(evento.type == SDL_QUIT) fin = true;

            if(evento.type == SDL_KEYDOWN) {
                john.movimiento();
                if(evento.key.keysym.sym == SDLK_ESCAPE) {
                    fin = true;
                }
                if(evento.key.keysym.sym == SDLK_p)
                {
                    if(spawner == true)
                    {
                       spawner = false;
                    }
                    else
                    spawner = true;
                }
                if(evento.key.keysym.sym == SDLK_o)
                {
                    if(freeze == true)
                    {
                       freeze = false;
                    }
                    else
                    freeze = true;
                }
            }
            else if( evento.type == SDL_KEYUP ){
                john.frenar();
            }

            else if( evento.type == SDL_MOUSEMOTION) {
                ultmousex = evento.motion.x;
                ultmousey = evento.motion.y;
            }

            else if(evento.type == SDL_MOUSEBUTTONDOWN)
            {
                Mix_PlayChannel(-1, rocketshoot, 0);

                i = 0;
                if(john.get_shoot_cooldown() < 1) {
                    while(i < 3) {
                        if(rocket[i].get_activo() == false) {
                            rocket[i].set_activo(true);
                            rocket[i].set_estado(1);
                            rocket[i].set_mousex(ultmousex);
                            rocket[i].set_mousey(ultmousey);
                            rocket[i].set_jposx(john.get_posx()+48);
                            rocket[i].set_jposy(john.get_posy()+30);
                            rocket[i].set_hby(john.get_posy()+20);
                            rocket[i].set_hbx(john.get_posx()+48);
                            rocket[i].trayectoriaRocket();
                            rocket[i].definir_frame();
                            i = 5;
                            john.set_shoot_cooldown(20);
                        }
                        i++;
                    }
                }

            }
        }

    ///PASTILLAS --------------

        if(medpack.get_cooldown() > 0) {
            medpack.set_cooldown(medpack.get_cooldown() - 1);
        }

        if((medpack.get_cooldown() == 0) && (medpack.get_estado() == 0)) {
            medpack.set_estado(2);
        }

        if((segundos > 0) && (segundos % 20 == 0) && (medpack.get_estado() == 2)) {
            medpack.spawn_hard();
        }

        if(medpack.get_estado() == 1) {
            if (check_collision(john.get_hitbox(), medpack.get_pickbox())) {
                john.set_salud(john.get_salud() + 1);
                medpack.despawn();
            }
        }

        ///Funciones de movimiento:
        john.mover();

        if(john.get_estado() == 3 && john.get_framecont() == 0) {
            Mix_PlayChannel(-1, jump, 0);
        }

/// //////////// EXPLOSION ////////////////

        for(i=0; i<3; i++) {
            if(contexp[i] != 0)
            {
                contexp[i]++;
                if(contexp[i] > 20)
                {
                    contexp[i] = 0;
                    explosion[i].x = 1200;
                    explosion[i].y = - 150;
                }
            }
        }

///ENEMIGOS//////////////////////////////////////////////////////////////

        for(i=0; i<cantGluttons; i++) {
        if(vGluttons[i].get_activo() == true) {
            if(vGluttons[i].get_cooldown() > 0) {
                vGluttons[i].set_cooldown(vGluttons[i].get_cooldown()-1);
            }

            if(check_collision(john.get_hitbox(), vGluttons[i].get_punchbox()) && vGluttons[i].get_estado() < 3 && vGluttons[i].get_cooldown() == 0 && vGluttons[i].get_salud() > 0) {
                SDL_Delay(100);
                john.set_framecont(0);
                john.set_estado(6);
                vGluttons[i].set_framecont(0);
                vGluttons[i].set_estado(5);
                john.set_salud(john.get_salud()-1);
            }


            for(offsetx=0; offsetx<3; offsetx++) {

                if(check_collision(explosion[offsetx], vGluttons[i].get_hitbox()) && vGluttons[i].get_airborne()== false)
                {
                    vGluttons[i].set_framecont(0);
                    vGluttons[i].set_estado(4);
                }
            }
            offsetx = 0;
            while(offsetx < 3) {
                if(check_collision(vGluttons[i].get_hitbox(), rocket[offsetx].get_hitbox()) && vGluttons[i].get_airborne() == true && vGluttons[i].get_salud() > 0) ///airshot
                {
                    vGluttons[i].set_salud(vGluttons[i].get_salud()-1);
                    explosion[offsetx].x = rocket[offsetx].get_hbx();
                    explosion[offsetx].y = rocket[offsetx].get_hby();
                    rocket[offsetx].set_hbx(-25);
                    rocket[offsetx].set_hby(-25);
                    rocket[offsetx].set_activo(false);
                    rocket[offsetx].set_estado(0);
                    contexp[offsetx]++;
                } ///ded
                offsetx++;
            }

            vGluttons[i].accion(john.get_posx());
            if(freeze == true)
            {
                vGluttons[i].freeze();
            }
            else
            {
                vGluttons[i].mover();
            }

            }

            if(vGluttons[i].get_salud() < 1 && vGluttons[i].get_posy() >= 400) {
                rank.set_puntaje(rank.get_puntaje()+(100*multiplier));
                rank.set_muertes(rank.get_muertes()+1);
                muertesrecientes++;
                vGluttons[i].set_activo(false);
                vGluttons[i].set_posx(-100);
                vGluttons[i].set_posy(400);
                vGluttons[i].set_punchx(9999);
                vGluttons[i].set_punchy(9999);
                vGluttons[i].set_airborne(false);
                vGluttons[i].set_salud(1);
            }
        }


        ///enemigos grandes
        for(i=0; i<cantMagnatrons; i++)
        {
            if(vMagnatrons[i].get_activo() == true) {
            if(vMagnatrons[i].get_cooldown() > 0) {
                vMagnatrons[i].set_cooldown(vMagnatrons[i].get_cooldown()-1);
            }

            if(check_collision(john.get_hitbox(), vMagnatrons[i].get_punchbox()) && vMagnatrons[i].get_estado() < 3 && vMagnatrons[i].get_cooldown() == 0 && vMagnatrons[i].get_salud() > 0) {
                SDL_Delay(100);
                john.set_framecont(0);
                john.set_estado(6);
                vMagnatrons[i].set_framecont(0);
                vMagnatrons[i].set_estado(5);
                john.set_salud(john.get_salud()-2);
            }

            for(offsetx=0; offsetx<3; offsetx++) {
                if(check_collision(explosion[offsetx], vMagnatrons[i].get_hitbox()))
                    {
                    vMagnatrons[i].set_framecont(0);
                    vMagnatrons[i].set_estado(4);
                    }  ///Se le puede disparar de nuevo en el aire
                if(check_collision(explosion[offsetx], vMagnatrons[i].get_hitbox()) && vMagnatrons[i].get_airborne()== false)
                {
                    vMagnatrons[i].set_framecont(0);
                    vMagnatrons[i].set_estado(4);
                }
            }
            offsetx = 0;
            while(offsetx < 3) {
                if(check_collision(vMagnatrons[i].get_hitbox(), rocket[offsetx].get_hitbox()) && vMagnatrons[i].get_airborne() == true && vMagnatrons[i].get_salud() > 0) ///airshot
                {
                    vMagnatrons[i].set_salud(vMagnatrons[i].get_salud()-1);
                    explosion[offsetx].x = rocket[offsetx].get_hbx();
                    explosion[offsetx].y = rocket[offsetx].get_hby();
                    rocket[offsetx].set_hbx(-25);
                    rocket[offsetx].set_hby(-25);
                    rocket[offsetx].set_activo(false);
                    rocket[offsetx].set_estado(0);
                    contexp[offsetx]++;
                } ///ded
                offsetx++;
            }

            vMagnatrons[i].accion(john.get_posx());
            if(freeze == true)
            {
                vMagnatrons[i].freeze();
            }
            else
            {
                vMagnatrons[i].mover();
            }


            if(vMagnatrons[i].get_salud() < 1 && vMagnatrons[i].get_posy() >= 400) {
                rank.set_puntaje(rank.get_puntaje()+(300*multiplier));
                rank.set_muertes(rank.get_muertes()+1);
                muertesrecientes++;
                vMagnatrons[i].set_activo(false);
                vMagnatrons[i].set_posx(-100);
                vMagnatrons[i].set_posy(400);
                vMagnatrons[i].set_punchx(9999);
                vMagnatrons[i].set_punchy(9999);
                vMagnatrons[i].set_airborne(false);
                vMagnatrons[i].set_salud(1);
            }

        }

        }

        ///BLIP BLIP BOOM///////////////
        for(i=0; i<cantBlips; i++)
        {
            if(vBlip[i].get_activo() == true)
            {
                if(check_collision(vBlip[i].get_hitbox(), floor)){
                    vExp[i].spawn(vBlip[i].get_hitboxx(), vBlip[i].get_hitboxy()+40);
                    vBlip[i].set_estado(2);
                }

                if(vBlip[i].get_salud() < 1) {
                    rank.set_puntaje(rank.get_puntaje()+(50*multiplier));
                    rank.set_muertes(rank.get_muertes()+1);
                    muertesrecientes++;
                    vBlip[i].set_estado(2);
                    vExp[i].spawn(vBlip[i].get_hitboxx(), vBlip[i].get_hitboxy());
                }

                vBlip[i].accion(john.get_posx());
                if(freeze == true)
                {
                    vBlip[i].set_xvel(0);
                }
                else
                {
                    vBlip[i].mover();
                }


                offsetx = 0;
                while(offsetx < 3) {
                    if(check_collision(vBlip[i].get_hitbox(), rocket[offsetx].get_hitbox()) && vBlip[i].get_salud() > 0)
                    {
                        vBlip[i].set_salud(vBlip[i].get_salud()-1);
                        explosion[offsetx].x = rocket[offsetx].get_hbx();
                        explosion[offsetx].y = rocket[offsetx].get_hby();
                        rocket[offsetx].set_hbx(-25);
                        rocket[offsetx].set_hby(-25);
                        rocket[offsetx].set_activo(false);
                        rocket[offsetx].set_estado(0);
                        contexp[offsetx]++;
                    }
                    offsetx++;
                }

            }
            if(vExp[i].get_estado() > 0)
            {
                vExp[i].do_things();

                if(check_collision(john.get_hitbox(),vExp[i].get_hitbox()) && vExp[i].get_estado() == 1)
                {
                    SDL_Delay(100);
                    vExp[i].set_estado(2);
                    john.set_framecont(0);
                    john.set_estado(6);
                    john.set_salud(john.get_salud()-1);
                }
            }
        }

        if(ultmousex >= john.get_posx()+48)
        {
            john.set_orientacion(true);
        }
        else
        {
            john.set_orientacion(false);
        }

        if(ultmousex > john.get_posx() && ultmousey > john.get_posy() + 50)
        {
            john.set_apuntando(3); ///abajo derecha
        }
        else if(ultmousex > john.get_posx() && ultmousey < john.get_posy() - 50)
        {
            john.set_apuntando(1); ///arriba derecha
        }
        else if(ultmousex < john.get_posx() && ultmousey > john.get_posy() + 50)
        {
            john.set_apuntando(4); ///abajo derecha
        }
        else if(ultmousex < john.get_posx() && ultmousey < john.get_posy() - 50)
        {
            john.set_apuntando(0); ///arriba derecha
        }
        else{
            john.set_apuntando(2); ///derecha
        }

    /// ///////////////// MISILES ////////////////////////////
        for(i=0; i<3; i++) {
            if(rocket[i].get_activo())
            {
                if(rocket[i].get_estado()==1)
                {
                    rocket[i].viajeRocket2();
                }

                if(check_collision(rocket[i].get_hitbox(), floor))
                {
                    explosion[i].x = rocket[i].get_hbx();
                    explosion[i].y = 476;
                    rocket[i].set_activo(false);
                    contexp[i]++;
                }

                if(rocket[i].get_hbx()< -100 || rocket[i].get_hbx() > SCREEN_WIDTH+100 || rocket[i].get_hby() < -100)
                {
                    rocket[i].set_activo(false);
                }

                if(rocket[i].get_activo()==false)
                {
                    rocket[i].set_hbx(-25);
                    rocket[i].set_hby(-25);
                }

            }
        }

        ///Spawn de enemigos:
        if(ciclo_spawn >= 2 && spawner == true) {
            ciclo_spawn = 0;
            i = 0;
            while(i<cantGluttons) {
                if(vGluttons[i].get_activo() == false){
                    vGluttons[i].set_activo(true);
                    vGluttons[i].spawn();
                    vGluttons[i].set_salud(1);
                    i=cantGluttons+1;
                }
                i++;
            }
        }


        if(ciclo_spawn_grandes >= 5 && spawner == true) {
            ciclo_spawn_grandes = 0;
            i = 0;
            while(i<cantMagnatrons) {
                if(vMagnatrons[i].get_activo() == false){
                    vMagnatrons[i].set_activo(true);
                    vMagnatrons[i].spawn();
                    vMagnatrons[i].set_salud(2);
                    i=cantMagnatrons+1;
                }
                i++;
            }
        }

        if(ciclo_spawn_blips >= 10 && spawner == true)
        {
            ciclo_spawn_blips = 0;
            i = 0;
            while(i<cantBlips)
            {
                if(vBlip[i].get_activo() == false)
                {
                    vBlip[i].spawn();
                    i=cantBlips+1;
                }
                i++;
            }
        }


            if(rank.get_puntaje() >= 2500 && flagpuntaje == 0)
            {
                cantGluttons = 6;
                cantMagnatrons = 4;
                cantBlips = 2;
                flagpuntaje = 1;
            }

            if(rank.get_puntaje() >= 7500 && flagpuntaje == 1)
            {
                cantGluttons = 7;
                cantMagnatrons = 5;
                flagpuntaje = 2;
            }

            if(rank.get_puntaje() >= 10000 && flagpuntaje == 2)
            {
                cantGluttons = 10;
                cantMagnatrons = 6;
                cantBlips = 4;
                flagpuntaje = 3;

            }

            if(rank.get_puntaje() >= 15000 && flagpuntaje == 3)
            {
                cantGluttons = 15;
                cantMagnatrons = 7;
                flagpuntaje = 4;
            }
            if(rank.get_puntaje() >= 20000 && flagpuntaje == 4)
            {
                cantGluttons = 20;
                cantMagnatrons = 10;
                cantBlips = 5;
                flagpuntaje = 5;
            }





        ///Multiplicador de puntaje
        if(muertesrecientes > 5 && multiplier == 1) {
            multiplier++;
            countdown = 30;
            muertesrecientes = 0;
        }
        else if(muertesrecientes > 10 && multiplier == 2) {
            multiplier++;
            countdown = 20;
            muertesrecientes = 0;
        }

        if(john.get_salud() < 1) {
            fin = true;
            mensaje = TTF_RenderText_Solid(fontbig, "G  A  M  E    O  V  E  R" ,text_color);
        }

        itoa(segundos, tiempo, 10);
        cronometro = TTF_RenderText_Solid(font, tiempo, text_color);
        itoa(john.get_salud(), charvida, 10);
        vida = TTF_RenderText_Solid(font, charvida, text_color);
        itoa(rank.get_puntaje(), puntaje, 10);
        puntos = TTF_RenderText_Solid(font, puntaje, text_color);
        itoa(rank.get_muertes(), kills, 10);
        muertes = TTF_RenderText_Solid(font, kills, text_color);
        itoa(multiplier, mult, 10);
        multiplicador = TTF_RenderText_Solid(fontbig, mult, text_color);



        aplicarSuperficie(0, 0, fondo, screen);
        for(i=0; i<cantGluttons; i++) {
            aplicarSuperficie(vGluttons[i].get_posx(), vGluttons[i].get_posy(), enemigochico, screen, &enemigoclip[vGluttons[i].definir_frame(frame)]);
        }

        for(i=0; i<cantMagnatrons; i++)
        {
            aplicarSuperficie(vMagnatrons[i].get_posx(), vMagnatrons[i].get_posy(), enemigogrande, screen, &enemigograndeclip[vMagnatrons[i].definir_frame(frame)]);
        }
        for(i=0; i<3; i++) {
            aplicarSuperficie(rocket[i].get_hbx(), rocket[i].get_hby(), rocketimg, screen, &rocketclip[rocket[i].get_aframe()]);
        }

        for(i=0; i<cantBlips; i++)
        {
            aplicarSuperficie(vBlip[i].get_posx(), vBlip[i].get_posy(), enemigoblip, screen, &enemigoblipclip[vBlip[i].definir_frame(frame)]);
            aplicarSuperficie(vExp[i].get_hitboxx(), vExp[i].get_hitboxy(), blipexplosion, screen);
        }

        aplicarSuperficie(john.get_posx(), john.get_posy(), johnsheet, screen, &johnclip[john.definir_frame(frame)]);

        aplicarSuperficie(medpack.get_posx(), medpack.get_posy(), botiquin, screen, &botiquinclip[medpack.animar_hard(frame)]);

        for(i=0; i<3; i++) {
            aplicarSuperficie(explosion[i].x, explosion[i].y, explosionimg, screen);
        }


        aplicarSuperficie(0, 0, HUD, screen);

        aplicarSuperficie(120, 14, vida, screen);
        aplicarSuperficie(850, 14, cronometro, screen);
        aplicarSuperficie(320, 14, puntos, screen);
        aplicarSuperficie(600, 14, muertes, screen);
        aplicarSuperficie(880, 50, multiplicador, screen);
        aplicarSuperficie(230, 250, mensaje, screen);
        aplicarSuperficie(ultmousex-16, ultmousey-16, cursor, screen);
        SDL_Flip(screen);

        SDL_FreeSurface(cronometro);
        SDL_FreeSurface(vida);
        SDL_FreeSurface(puntos);
        SDL_FreeSurface(multiplicador);
        SDL_FreeSurface(muertes);
        SDL_FreeSurface(mensaje);

        if(john.get_salud() < 1) {
            SDL_Delay(2000);
            HARDEND(rank, segundos);
        }

        if((fps.get_ticks() < 1000 / fpeses))
        {
            SDL_Delay((1000 / fpeses) - fps.get_ticks());
        }
    }
    ///Fin del ciclo//////////////////////////////////////////////////////

    ///Se liberan todos los graficos:
    SDL_FreeSurface(HUD);
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(johnsheet);
    SDL_FreeSurface(blipexplosion);
    SDL_FreeSurface(enemigochico);
    SDL_FreeSurface(enemigoblip);
    SDL_FreeSurface(enemigogrande);
    SDL_FreeSurface(rocketimg);
    SDL_FreeSurface(explosionimg);
    SDL_ShowCursor(SDL_ENABLE);

    if(Mix_PlayingMusic() != 0){
        Mix_HaltMusic();
    }
    Mix_FreeMusic(theme);
    Mix_FreeChunk(jump);
    Mix_FreeChunk(rocketshoot);
    ///Mix_FreeChunk(smalldeath);
}

void MENU() {
    SDL_Surface* menu = NULL;
    SDL_Surface* brut = NULL;
    SDL_Surface* hard = NULL;
    SDL_Surface* exit = NULL;
    menu = cargarImagen("graphics\\menu\\fondo.bmp");
    brut = cargarImagen("graphics\\menu\\BRUTselected.bmp");
    hard = cargarImagen("graphics\\menu\\HARDselected.bmp");
    exit = cargarImagen("graphics\\menu\\EXITselected.bmp");
    objeto botonbrut, botonhard, botonexit;

    SDL_Rect brutrect, hardrect, exitrect;
    brutrect.h = 400;
    brutrect.w = 500;
    brutrect.x = 0;
    brutrect.y = 0;

    hardrect.h = 400;
    hardrect.w = 500;
    hardrect.x = 500;
    hardrect.y = 0;

    exitrect.h = 120;
    exitrect.w = 900;
    exitrect.x = 20;
    exitrect.y = 420;

    bool salir = false;

    while(salir == false) {
        aplicarSuperficie(0, 0, menu, screen);
        if(botonbrut.get_estado() == 1) {
            aplicarSuperficie(botonbrut.get_posx(), botonbrut.get_posy(), brut, screen);
        }
        if(botonhard.get_estado() == 1) {
            aplicarSuperficie(botonhard.get_posx(), botonhard.get_posy(), hard, screen);
        }
        if(botonexit.get_estado() == 1) {
            aplicarSuperficie(botonexit.get_posx(), botonexit.get_posy(), exit, screen);
        }

        SDL_Flip(screen);

        while(SDL_PollEvent(&evento)) {

            if(evento.type == SDL_QUIT) salir = true;

            if(evento.type == SDL_KEYDOWN) {

                switch(evento.key.keysym.sym) {
                case(SDLK_LEFT):
                    botonbrut.set_estado(1);
                    botonhard.set_estado(0);
                    botonexit.set_estado(0);
                    break;
                case(SDLK_RIGHT):
                    botonbrut.set_estado(0);
                    botonhard.set_estado(1);
                    botonexit.set_estado(0);
                    break;
                case(SDLK_DOWN):
                    botonbrut.set_estado(0);
                    botonhard.set_estado(0);
                    botonexit.set_estado(1);
                    break;
                case(SDLK_ESCAPE):
                    salir = true;
                    break;
                case(SDLK_RETURN):
                    if(botonbrut.get_estado()) BRUT();
                    if(botonhard.get_estado()) HARD();
                    if(botonexit.get_estado()) salir = true;
                    break;
                default:
                    break;
                }
            }

            if(evento.type == SDL_MOUSEMOTION) /// si se mueve el mouse
            {
                if (checkpos(brutrect, evento.motion.x, evento.motion.y)) ///si el mouse esta sobre la posicion del rectangulo ya situado encima del boton
                {
                    botonbrut.set_estado(1);
                    botonhard.set_estado(0);
                    botonexit.set_estado(0);
                }

                if(checkpos(hardrect, evento.motion.x, evento.motion.y))
                {
                    botonbrut.set_estado(0);
                    botonhard.set_estado(1);
                    botonexit.set_estado(0);
                }

                if(checkpos(exitrect, evento.motion.x, evento.motion.y))
                {
                    botonbrut.set_estado(0);
                    botonhard.set_estado(0);
                    botonexit.set_estado(1);
                }
            }
            if(evento.type == SDL_MOUSEBUTTONDOWN)
            {
                if(botonbrut.get_estado()) BRUT();
                if(botonhard.get_estado()) HARD();
                if(botonexit.get_estado()) salir = true;
            }
        }

    }

    SDL_FreeSurface(menu);
    SDL_FreeSurface(brut);
    SDL_FreeSurface(exit);
    SDL_FreeSurface(hard);
}

#endif // FUNCIONES_H_INCLUDED
