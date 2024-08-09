#ifndef CLASEJUGADORKURT_H_INCLUDED
#define CLASEJUGADORKURT_H_INCLUDED

class jugadorkurt: public entidad{
protected:
    SDL_Rect hitbox;
    SDL_Rect kickbox;
    SDL_Rect grabbox;
public:
    ~jugadorkurt(){}
    ///DEBUG:
    int get_get() {return hitbox.x+hitbox.w;}
    int get_git() {return hitbox.y+hitbox.h;}
    ///
    SDL_Rect get_hitbox() {return hitbox;}
    SDL_Rect get_kickbox() {return kickbox;}
    SDL_Rect get_grabbox() {return grabbox;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    void set_kickbox(SDL_Rect aux) {kickbox = aux;}
    void set_grabbox(SDL_Rect aux) {grabbox = aux;}
    void set_hitboxh(int aux) {hitbox.h = aux;}
    void set_hitboxw(int aux) {hitbox.w = aux;}
    jugadorkurt(){
        cooldown = 0;
        salud = 3;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = true;
        kickbox.h = 50;
        kickbox.w = 40;
        kickbox.x = -100;
        grabbox.h = 40;
        grabbox.w = 24;
        kickbox.y = -100;
        grabbox.x = -100;
        grabbox.y = -100;
        hitbox.h = 0;
        hitbox.w = 0;
    }
    ///calcula en que dirección se tendrá que mover
    void movimiento() {
        switch(evento.key.keysym.sym) {
        case(SDLK_LEFT):
            xvel -= 3;
            break;
        case(SDLK_RIGHT):
            xvel += 3;
            break;
        case(SDLK_DOWN):
            yvel += 3;
            break;
        case(SDLK_UP):
            yvel -= 3;
            break;
        case(SDLK_a):
            if(cooldown == 0 && estado < 2) {
                estado = 3; ///el estado tres hace que el jugador "dashee"
            }
            break;
        case(SDLK_s):
            if(estado < 2) {
                estado = 2; ///el estado dos hace que el jugador patee
            }
            break;
        case(SDLK_d):
            if(estado < 2) {
                estado = 4; ///el estado cuatro inicia un intento de agarrar
            }
            break;
        default:
            break;
        }
    }
    ///compensa la velocidad actual para frenar al jugador
    void frenar() {
        switch( evento.key.keysym.sym ){
            case(SDLK_LEFT):
                xvel += 3;
                break;
            case(SDLK_RIGHT):
                xvel -= 3;
                break;
            case(SDLK_DOWN):
                yvel -= 3;
                break;
            case(SDLK_UP):
                yvel += 3;
                break;
            default:
                break;
        }
    }
    ///mueve al jugador
    void mover() {
        if(estado == 0 || estado == 1) {
            posx += xvel;

            if( (posx < 0) || (posx + width > SCREEN_WIDTH))
            {
                posx -= xvel;
            }
            posy += yvel;
            if( (posy < 105) || (posy + height > SCREEN_HEIGHT - 60))
            {
                posy -= yvel;

            }
            hitbox.x = posx+40;
            hitbox.y = posy+20;
            if(xvel > 0) {
                orientacion = true;
            }
            else if(xvel < 0) {
                orientacion = false;
            }
        }
    }
    ///comprueba y devuelve el frame que debería mostrar
    int definir_frame(int frame) {
        switch(estado) {
        case(0): ///idle animation
            if(frame < 15) {
                aframe = 8;
            }
            else if((frame >= 15 && frame < 30) || (frame >= 45)) {
                aframe = 9;
            }
            else{
                aframe = 10;
            }
            break;
        case(1): ///walking cycle
            if((frame < 8) || (frame > 30 && frame <= 38)) {
                aframe = 0;
            }
            else if((frame > 8 && frame <= 15) || (frame > 23 && frame <= 30) || (frame > 38 && frame <= 45) || (frame > 53)) {
                aframe = 1;
            }
            else{
                aframe = 2;
            }
            break;

        case(2): ///kick
            if(framecont < 10) {
                aframe = 4;
                if(framecont == 0) {
                    if(orientacion) {
                        kickbox.x = posx + 60;
                        kickbox.y = posy + 32;
                    }
                    else{
                        kickbox.x = posx + 8;
                        kickbox.y = posy + 32;
                    }
                }
                else{
                    kickbox.x = -100;
                    kickbox.y = -100;
                }
            }
            else if(framecont >= 10) {
                aframe = 5;
            }
            framecont++;
            if(framecont > 22) {
                estado = 0;
                framecont = 0;
            }
            break;
        case(3): ///dash
            aframe = 11;
            hitbox.x = -111;
            hitbox.y = -111;
            if(orientacion == true) {
                posx += 7;
                if(posx + width > SCREEN_WIDTH)
                {
                    posx -= 7;
                }
            }
            else{
                posx -= 7;
                if(posx < 0)
                {
                    posx += 7;
                }
            }

            framecont++;
            if(framecont > 14) {
                estado = 0;
                framecont = 0;
                cooldown = 30;
                hitbox.x = posx+28;
                hitbox.y = posy+20;
            }
            break;
        case(4): ///grab
            aframe = 6;
            if(framecont == 10) {
                if(orientacion) {
                    grabbox.x = posx + 62;
                    grabbox.y = posy + 22;
                }
                else{
                    grabbox.x = posx + 12;
                    grabbox.y = posy + 22;
                }
            }
            else{
                grabbox.x = -100;
                grabbox.y = -100;
            }
            framecont++;
            if(framecont > 14) {
                estado = 0;
                framecont = 0;
            }
            break;
        case(5):
            grabbox.x = -100;
            grabbox.y = -100;
            aframe = 3;
            framecont++;
            if(framecont > 19) {
                estado = 0;
                framecont = 0;
            }
            break;
        case(6):
            hitbox.x = 600;
            hitbox.y = 600;
            aframe = 7;
            framecont++;
            if(framecont > 15) {
                estado = 0;
                framecont = 0;
                hitbox.x = posx+28;
                hitbox.y = posy+20;
            }
            break;
        default:
            aframe = 0;
            break;
        }
        if(estado < 2) {
            if(xvel == 0 && yvel == 0) {
                estado = 0;
            }
            if(xvel != 0 || yvel != 0) {
                estado = 1;
            }
        }
        if(orientacion == false) {
            aframe += 12;
        }
        return aframe;
    }
};

#endif // CLASEJUGADORKURT_H_INCLUDED
