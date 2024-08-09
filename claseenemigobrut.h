#ifndef CLASEENEMIGOBRUT_H_INCLUDED
#define CLASEENEMIGOBRUT_H_INCLUDED

class enemigobrut:public entidad{
private:
    bool activo;
    SDL_Rect hitbox;
    SDL_Rect punchbox;
    SDL_Rect throwbox;
public:
    ~enemigobrut(){}
    ///DEBUG:
    int get_get() {return punchbox.x-punchbox.w;}
    int get_git() {return punchbox.y+punchbox.h;}
    ///
    void set_punchx(int aux) {punchbox.x = aux;}
    void set_punchy(int aux) {punchbox.y = aux;}

    bool get_activo() {return activo;}
    SDL_Rect get_hitbox() {return hitbox;}
    SDL_Rect get_punchbox() {return punchbox;}
    SDL_Rect get_throwbox() {return throwbox;}
    void set_cooldown(int aux) {cooldown = aux;}
    void set_activo(bool aux) {activo = aux;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    void set_punchbox(SDL_Rect aux) {punchbox = aux;}
    void set_throwbox(SDL_Rect aux) {throwbox = aux;}
    enemigobrut() {
        salud = 2;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = false;
        activo = false;
        hitbox.h = 76;
        hitbox.w = 32;
        punchbox.h = 16;
        punchbox.w = 21;
        throwbox.h = 70;
        throwbox.w = 80;
        punchbox.x = -30;
        punchbox.y = -100;
        throwbox.x = -100;
        throwbox.y = -30;
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
            if(framecont > 89) {
                estado = 0;
                framecont = 0;
            }
            break;
        case(4): ///volaaaar
            if(framecont == 0) {
                if(kurtorient) {
                    orientacion = false;
                }
                else{
                    orientacion = true;
                }
            }

            if(framecont < 59) {
                if(orientacion == false) {
                    xvel = 0;
                    yvel = 0;
                    posx -= 5;
                }
                else{
                    xvel = 0;
                    yvel = 0;
                    posx += 5;
                }
                if(framecont < 20) {
                    posy -= 2;
                }
                if(framecont > 40) {
                    posy += 2;
                }
                throwbox.x = posx + 10;
                throwbox.y = posy + 20;
            }
            else{
                xvel = 0;
                yvel = 0;
                throwbox.x = -100;
                throwbox.y = -30;

            }
            framecont++;
            if(framecont > 69) {
                salud--;
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
            hitbox.y = posy + 20;
            if(orientacion) {
                punchbox.x = posx + 45;
                punchbox.y = posy + 30;
            }
            else{
                punchbox.x = posx + 30;
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
        if(estado == 4) {
            aframe = 5;
        }
        if(estado == 5) {
            aframe = 3;
        }
        if(orientacion == false) {
            aframe += 6;
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
    }

};

#endif // CLASEENEMIGOBRUT_H_INCLUDED
