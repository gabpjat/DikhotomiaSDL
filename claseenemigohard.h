#ifndef CLASEENEMIGOHARD_H_INCLUDED
#define CLASEENEMIGOHARD_H_INCLUDED

class enemigohard:public entidad {
private:
    bool activo;
    bool airborne;
    SDL_Rect hitbox;
    SDL_Rect punchbox;
    int variacion;
public:
    ~enemigohard(){}
    int get_get() {return punchbox.x-punchbox.w;}
    int get_git() {return punchbox.y+punchbox.h;}
    bool get_activo() {return activo;}
    bool get_airborne(){return airborne;} ///si se encuentra en el aire o no
    SDL_Rect get_hitbox() {return hitbox;}
    void set_activo(bool aux) {activo = aux;}
    void set_airborne(bool aux){airborne = aux;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    void set_punchx(int aux) {punchbox.x = aux;}
    void set_punchbox(SDL_Rect aux) {punchbox = aux;}
    void set_punchy(int aux) {punchbox.y = aux;}
    SDL_Rect get_punchbox() {return punchbox;}
    enemigohard() {
        salud = 1;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = false;
        activo = false;
        punchbox.h = 16;
        punchbox.w = 21;
        punchbox.x = -30;
        punchbox.y = -100;
        airborne = false;
        hitbox.h = 76;
        hitbox.w = 32;
    }
    void accion(float jugx){
        if(framecont == 0 && (estado == 0 || estado == 1 || estado == 2)) {
            estado = (rand() % 3);
        }
        switch(estado) {
        case(0):
            if(jugx < posx) {
                xvel = -2;
                orientacion = false;
            }
            else if (jugx > posx){
                xvel = 2;
                orientacion = true;
            }


            framecont += 10;
            break;
        case(1):
            xvel = 0;
            yvel = 0;
            framecont += 20;
            break;
        case(2):
            if(framecont == 0) {
            xvel = (rand() % 5) - 2;
            yvel = 0; ///solo quiero que se muevan en eje x
            }
            framecont += 15;
            break;
        case(3):
            xvel = 0;
            yvel = 0;
            framecont++;
            if(framecont == 60) {
                estado = 0;
                framecont = 0;
            }
            break;
        case(4): ///enviar al enemigo para arriba
            if(framecont == 0) {
                    xvel = (rand() % 5) - 2 ;
                    set_airborne(true);
                    variacion = (rand() % 30) + 20;

            }

            if(framecont < variacion) {
            posy -= 6;
            }
            else if(framecont >= variacion && framecont < variacion+variacion*0.5) {
            posy -= 3;
            }
            else if(framecont >= variacion+variacion*0.5 && framecont < variacion*2) {
            posy += 3;
            }
            else if(framecont >= variacion*2) {
            posy += 6;
            }

            framecont++;
            if(framecont > variacion*3)
            {
                estado = 1;
                framecont = 0;
                set_airborne(false);
                posy = 400;
            }

            break;
        case(5): ///golpear
            xvel = 0;
            yvel = 0;
            framecont++;
            if(framecont > 14) {
                estado = 0;
                framecont = 0;
                cooldown = 30;
            }
            break;
        }
        if(framecont > 200) {
            framecont = 0;
        }
    }

    ///mueve al enemigo
    void mover() {
            posx += xvel;
            posy += 0;
            hitbox.x = posx + 28;
            hitbox.y = posy + 20;
            if(posy + height > SCREEN_HEIGHT - 60)
            {
                posy -= yvel;
            }
            if(orientacion) {
                punchbox.x = posx + 45;
                punchbox.y = posy + 70;
            }
            else{
                punchbox.x = posx + 30;
                punchbox.y = posy + 70;
            }
    }

    void freeze()
    {
            posx += 0;
            posy += 0;
            hitbox.x = posx + 28;
            hitbox.y = posy + 20;
            if(posy + height > SCREEN_HEIGHT - 60)
            {
                posy -= yvel;
            }
            if(orientacion) {
                punchbox.x = posx + 45;
                punchbox.y = posy + 70;
            }
            else{
                punchbox.x = posx + 30;
                punchbox.y = posy + 70;
            }
    }

    int definir_frame(int frame) {
        aframe = 0;
        if(estado == 0 || estado == 2) {
            if(frame >= 45) {
                aframe = 2;
            }
            if(frame >= 15 && frame < 30) {
                aframe = 1;
            }
        }
        if(estado == 1) {
            aframe = 4;
        }
        if(estado == 4) {
            aframe = 5;
        }
        if(estado == 5) {
            aframe = 3;
        }
        if(salud < 1) {
            aframe = 6;
        }
        if(orientacion == false) {
            aframe += 7;
        }
        return aframe;
    }

    void spawn() {
        int aroab;
        aroab = (rand() % 2);
        if(aroab == 0) {
            posy = 400;
            posx = -100;
        }
        else{
            posy = 400;
            posx = 1000;
        }
        activo = true;
    }

};

class enemigograndehard:public entidad {
private:
    bool activo;
    bool airborne;
    SDL_Rect hitbox;
    SDL_Rect punchbox;
public:
    ~enemigograndehard(){}
    int get_get() {return punchbox.x-punchbox.w;}
    int get_git() {return punchbox.y+punchbox.h;}
    bool get_activo() {return activo;}
    bool get_airborne(){return airborne;} ///si se encuentra en el aire o no
    SDL_Rect get_hitbox() {return hitbox;}
    void set_activo(bool aux) {activo = aux;}
    void set_airborne(bool aux){airborne = aux;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    void set_punchx(int aux) {punchbox.x = aux;}
    void set_punchbox(SDL_Rect aux) {punchbox = aux;}
    void set_punchy(int aux) {punchbox.y = aux;}
    SDL_Rect get_punchbox() {return punchbox;}
    enemigograndehard() {
        salud = 2;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = false;
        activo = false;
        punchbox.h = 16;
        punchbox.w = 21;
        punchbox.x = -30;
        punchbox.y = -100;
        airborne = false;
        hitbox.h = 82;
        hitbox.w = 44;
    }
    void accion(float jugx){
        if(framecont == 0 && (estado == 0 || estado == 1 || estado == 2)) {
            estado = (rand() % 3);
        }
        switch(estado) {
        case(0):
            if(jugx < posx) {
                xvel = -1;
                orientacion = false;
            }
            else if (jugx > posx){
                xvel = 1;
                orientacion = true;
            }


            framecont += 10;
            break;
        case(1):
            xvel = 0;
            yvel = 0;
            framecont += 20;
            break;
        case(2):
            if(framecont == 0) {
            xvel = (rand() % 5) - 2;
            yvel = 0; ///solo quiero que se muevan en eje x
            }
            framecont += 15;
            break;
        case(3):
            xvel = 0;
            yvel = 0;
            framecont++;
            if(framecont == 60) {
                estado = 0;
                framecont = 0;
            }
            break;
        case(4): ///enviar al enemigo para arriba
            if(framecont == 0) {
                    xvel = (rand() % 5) - 2 ;
                    set_airborne(true);
            }

            if(framecont < 20) {
            posy -= 4;
            }
            else if(framecont >= 20 && framecont < 30) {
            posy -= 2;
            }
            else if(framecont >= 50 && framecont < 60) {
            posy += 2;
            }
            else if(framecont >= 60) {
            posy += 7;
            }

            framecont++;
            if(posy >= 400)
            {
                estado = 1;
                framecont = 0;
                set_airborne(false);
                posy = 400;
                if(salud > 0) {
                    salud = 2;
                }
            }

            break;
        case(5): ///golpear
            xvel = 0;
            yvel = 0;
            framecont++;
            if(framecont > 14) {
                estado = 0;
                framecont = 0;
                cooldown = 70;
            }
            break;
        }
        if(framecont > 200) {
            framecont = 0;
        }
    }

    ///mueve al enemigo
    void mover() {
            posx += xvel;
            posy += 0;
            hitbox.x = posx + 28;
            hitbox.y = posy + 20;
            if(posy + height > SCREEN_HEIGHT - 60)
            {
                posy -= yvel;
            }
            if(orientacion) {
                punchbox.x = posx + 45;
                punchbox.y = posy + 70;
            }
            else{
                punchbox.x = posx + 30;
                punchbox.y = posy + 70;
            }
    }

    void freeze()
    {
            posx += 0;
            posy += 0;
            hitbox.x = posx + 28;
            hitbox.y = posy + 20;
            if(posy + height > SCREEN_HEIGHT - 60)
            {
                posy -= yvel;
            }
            if(orientacion) {
                punchbox.x = posx + 45;
                punchbox.y = posy + 70;
            }
            else{
                punchbox.x = posx + 30;
                punchbox.y = posy + 70;
            }
    }

    int definir_frame(int frame) {
        aframe = 0;
        if(estado == 0 || estado == 2) {
            if(frame >= 45) {
                aframe = 2;
            }
            if(frame >= 15 && frame < 30) {
                aframe = 1;
            }
        }
        if(estado == 1) {
            aframe = 4;
        }
        if(estado == 4) {
            aframe = 5;
        }
        if(estado == 5) {
            aframe = 3;
        }
        if(salud < 1) {
            aframe = 6;
        }
        if(orientacion == false) {
            aframe += 7;
        }
        return aframe;
    }

    void spawn() {
        int aroab;
        aroab = (rand() % 2);
        if(aroab == 0) {
            posy = 400;
            posx = -100;
        }
        else{
            posy = 400;
            posx = 1000;
        }
        activo = true;
    }

};

class blipexplosionhard:public objeto{
private:
    int framecont;
    SDL_Rect hitbox;
public:
    int get_framecont(){return framecont;}
    SDL_Rect get_hitbox() {return hitbox;}
    void set_framecont(int aux) {framecont = aux;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    int get_hitboxx(){return hitbox.x;}
    int get_hitboxy(){return hitbox.y;}
    blipexplosionhard() {
        estado = 0;
        framecont = 0;
        hitbox.x = 9797;
        hitbox.y = 9797;
        hitbox.h = 40;
        hitbox.w = 40;
    }
    void spawn(int posx, int posy) {
        estado = 1;
        framecont = 0;
        hitbox.x = posx;
        hitbox.y = posy;
    }
    void do_things(){
        framecont++;
        if(framecont > 20) {
            estado = 0;
            hitbox.x = 9797;
            hitbox.y = 9797;
        }
    }
};

class enemigobliphard:public entidad {
private:
    bool activo;
    SDL_Rect hitbox;
public:
    ~enemigobliphard(){}
    bool get_activo() {return activo;}
    SDL_Rect get_hitbox() {return hitbox;}
    void set_activo(bool aux) {activo = aux;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    int get_hitboxx() {return hitbox.x;}
    int get_hitboxy() {return hitbox.y;}


    enemigobliphard() {
        salud = 1;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = false;
        activo = false;
        posx = 9999;
        posy = 300;
        hitbox.h = 72;
        hitbox.w = 52;
    }

    void accion(float jugx){
        switch(estado) {
        case(0): ///moverse horizontalmente
            if(jugx < posx) {
                xvel = -2;
                orientacion = false;
            }
            else if(jugx > posx){
                xvel = 2;
                orientacion = true;
            }
            if(jugx == posx || jugx == posx+1 || jugx == posx-1) {
                estado = 1;
            }
            break;
        case(1): ///caer
            xvel = 0;
            yvel = 10;
            break;
        case(2): ///explosion
            posx = 11111;
            posy = 11111;
            yvel = 0;
            activo = false;
            break;
        }
    }

    ///mueve al enemigo
    void mover() {
        posx += xvel;
        posy += yvel;
        hitbox.x = posx + 28;
        hitbox.y = posy + 20;
    }


    int definir_frame(int frame) {
        aframe = 0;
        if(estado == 0) {
            if(frame >= 45) {
                aframe = 0;

            }
            if(frame >= 15 && frame < 30) {
                aframe = 1;
            }
        }

        if(estado == 1) {
            aframe = 2;
        }
        if(salud < 1) {
            aframe = 2;
        }
        if(orientacion == false) {
            aframe += 3;
        }
        return aframe;
    }

    void spawn() {
        int aroab;
        aroab = (rand() % 2);
        if(aroab == 0) {
            posy = 200;
            posx = -100;
        }
        else{
            posy = 200;
            posx = 1000;
        }
        hitbox.x = posx;
        hitbox.y = posy;
        salud = 1;
        estado = 0;
        activo = true;
    }
};

#endif // CLASEENEMIGOHARD_H_INCLUDED
