#ifndef CLASEENEMIGOGRANDEBRUT_H_INCLUDED
#define CLASEENEMIGOGRANDEBRUT_H_INCLUDED

class enemigograndebrut:public entidad{
private:
    bool activo;
    SDL_Rect hitbox;
    SDL_Rect punchbox;
public:
    ~enemigograndebrut(){}
    ///DEBUG:
    int get_get() {return punchbox.x-punchbox.w;}
    int get_git() {return punchbox.y+punchbox.h;}
    ///
    void set_punchx(int aux) {punchbox.x = aux;}
    void set_punchy(int aux) {punchbox.y = aux;}

    bool get_activo() {return activo;}
    SDL_Rect get_hitbox() {return hitbox;}
    SDL_Rect get_punchbox() {return punchbox;}
    void set_cooldown(int aux) {cooldown = aux;}
    void set_activo(bool aux) {activo = aux;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    void set_punchbox(SDL_Rect aux) {punchbox = aux;}
    enemigograndebrut() {
        salud = 4;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = false;
        activo = false;
        hitbox.h = 90;
        hitbox.w = 32;
        punchbox.h = 20;
        punchbox.w = 45;
        punchbox.x = -30;
        punchbox.y = -100;
        cooldown = 0;
    }
    void accion(float jugx, float jugy, bool kurtorient){
        if(framecont == 0 && (estado == 0 || estado == 1 || estado == 2)) {
            estado = (rand() % 3);
        }
        switch(estado) {
        case(0): ///moverse hacia el jugador
            if(jugx < posx) {
                xvel = -1;
                orientacion = false;
            }
            else if (jugx > posx){
                xvel = 1;
                orientacion = true;
            }
            if(jugy < posy) {
                yvel = -1;
            }
            else if(jugy > posy) {
                yvel = 1;
            }
            if(jugx == posx) {
                xvel = 0;
            }
            if(jugy == posy) {
                yvel = 0;
            }
            framecont += 10;
            if(framecont > 200) {
                framecont = 0;
            }
            break;
        case(1): ///quedarse quieto
            xvel = 0;
            yvel = 0;
            framecont += 20;
            if(framecont > 200) {
                framecont = 0;
            }
            break;
        case(2): ///moverse aleatoriamente
            if(framecont == 0) {
            xvel = (rand() % 3) - 1;
            yvel = (rand() % 3) - 1;
            }
            framecont += 15;
            if(framecont > 200) {
                framecont = 0;
            }
            break;
        case(3): ///estar aturdido
            xvel = 0;
            yvel = 0;
            framecont++;
            if(framecont > 29) {
                estado = 0;
                framecont = 0;
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
        default:
            break;
        }

    }
    void mover() {
            posx += xvel;
            posy += yvel;
            if( (posy < 105) || (posy + height > SCREEN_HEIGHT - 60))
            {
                posy -= yvel;
            }
            hitbox.x = posx + 32;
            hitbox.y = posy + 6;
            if(orientacion) {
                punchbox.x = posx + 48;
                punchbox.y = posy + 30;
            }
            else{
                punchbox.x = posx + 3;
                punchbox.y = posy + 30;
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
        if(estado == 3) {
            aframe = 4;
        }
        if(estado == 5) {
            aframe = 3;
        }
        if(orientacion == false) {
            aframe += 5;
        }
        return aframe;
    }
    void spawn() {
        int aroab;
        aroab = (rand() % 2);
        if(aroab == 0) {
            posy = (rand() % 270) + 100;
            posx = -100;
        }
        else{
            posy = (rand() % 270) + 100;
            posx = 1000;
        }
        activo = true;
        estado = 0;
        framecont = 0;
        salud = 4;
    }

};

#endif // CLASEENEMIGOGRANDEBRUT_H_INCLUDED
