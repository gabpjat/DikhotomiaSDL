#ifndef CLASEJUGADORHARD_H_INCLUDED
#define CLASEJUGADORHARD_H_INCLUDED

class jugadorhard: public entidad{
protected:
    bool piso;
    int shoot_cooldown;
    SDL_Rect hitbox;
    SDL_Rect kickbox;
    SDL_Rect grabbox;
    float gravedad;
    int apuntando;

public:
    ~jugadorhard(){}
    int get_shoot_cooldown(){return shoot_cooldown;}
    void set_shoot_cooldown(int aux) {shoot_cooldown = aux;}
    bool get_piso(){return piso;}
    SDL_Rect get_hitbox() {return hitbox;}
    void set_piso(bool aux){piso = aux;}
    void set_hitbox(SDL_Rect aux) {hitbox = aux;}
    void set_hitboxh(int aux){hitbox.h = aux;}
    void set_hitboxw(int aux){hitbox.w = aux;}
    int get_apuntando(){return apuntando;}
    void set_apuntando(int aux){apuntando = aux;}

    jugadorhard(){
        cooldown = 0;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = true;
        piso = true;
        gravedad = 1;
        hitbox.h = 0;
        hitbox.w = 0;
        apuntando = 2;

    }
    ///calcula en que dirección se tendrá que mover
    void movimiento() {

        switch(evento.key.keysym.sym) {
        case(SDLK_w):
            set_estado(3);
            break;
        case(SDLK_SPACE):
            set_estado(3);
            break;
        case(SDLK_UP):
            set_estado(3);
            break;
        case(SDLK_a):
            xvel-= 3;
            break;
        case(SDLK_LEFT):
            xvel-= 3;
            break;
        case(SDLK_s):
            break;
        case(SDLK_d):
            xvel +=3;
            break;
        case(SDLK_RIGHT):
            xvel +=3;
            break;
        default:
            break;
        }
    }
    ///compensa la velocidad actual para frenar al jugador
    void frenar() {
        switch( evento.key.keysym.sym ){
            case(SDLK_a):
                xvel += 3;
                break;
            case(SDLK_LEFT):
                xvel += 3;
                break;
            case(SDLK_d):
                xvel -= 3;
                break;
            case(SDLK_RIGHT):
                xvel -= 3;
                break;
            case(SDLK_s):
                break;
            case(SDLK_w):
                break;
            default:
                break;
        }
    }
    ///mueve al jugador
    void mover() {

            posx += xvel;

            if( (posx < 0) || (posx + width > SCREEN_WIDTH))
            {
                posx -= xvel;
            }
            posy += yvel;
            if((posy < 105) || (posy > 400))
            {
                posy -= yvel;

            }
            hitbox.x = posx+28;
            hitbox.y = posy+20;

    }
    ///comprueba y devuelve el frame que debería mostrar
    int definir_frame(int frame) {
        switch(estado) {
        case(0): ///idle animation

            if(apuntando == 2)
            {
                if(frame < 15) {
                    aframe = 0;
                }
                else if((frame >= 15 && frame < 30) || (frame >= 45)) {
                    aframe = 1;
                }
                else{
                    aframe = 0;
                }
            }
            if(apuntando == 1 || apuntando == 0) ///arriba
            {
                  if(frame < 15) {
                    aframe = 12;
                }
                else if((frame >= 15 && frame < 30) || (frame >= 45)) {
                    aframe = 13;
                }
                else{
                    aframe = 12;
                }
            }
             if(apuntando == 3 || apuntando == 4) ///abajo
            {
                  if(frame < 15) {
                    aframe = 6;
                }
                else if((frame >= 15 && frame < 30) || (frame >= 45)) {
                    aframe = 7;
                }
                else{
                    aframe = 6;
                }
            }

            break;
        case(1): ///walking cycle
            if(apuntando == 2)
            {
                    if((frame < 8) || (frame > 30 && frame <= 38))
                        {
                            aframe = 4;
                        }
                    else if((frame > 8 && frame <= 15) || (frame > 23 && frame <= 30) || (frame > 38 && frame <= 45) || (frame > 53))
                        {
                            aframe = 3;
                        }
                        else
                        {
                            aframe = 5;
                        }

            }
            if(apuntando == 1 || apuntando == 0) ///arriba
            {
                    if((frame < 8) || (frame > 30 && frame <= 38))
                        {
                            aframe = 16;
                        }
                    else if((frame > 8 && frame <= 15) || (frame > 23 && frame <= 30) || (frame > 38 && frame <= 45) || (frame > 53))
                        {
                            aframe = 15;
                        }
                        else
                        {
                            aframe = 17;
                        }
            }

            if(apuntando == 3 || apuntando == 4) ///abajo
            {
                    if((frame < 8) || (frame > 30 && frame <= 38))
                        {
                            aframe = 10;
                        }
                    else if((frame > 8 && frame <= 15) || (frame > 23 && frame <= 30) || (frame > 38 && frame <= 45) || (frame > 53))
                        {
                            aframe = 9;
                        }
                        else
                        {
                            aframe = 11;
                        }
            }


            break;
        case(3): ///saltar

        if(apuntando == 2) ///derecha
        {
            aframe = 2;
            if(framecont < 40) {
                posy -= 2.5;
            }
            if(framecont >= 40) {
                posy += 2.5;
            }
        }
        if(apuntando == 3 || apuntando == 4) ///abajo
        {
            aframe = 8;
            if(framecont < 40) {
                posy -= 2.5;
            }
            if(framecont >= 40) {
                posy += 2.5;
            }
        }

        if(apuntando == 1 || apuntando == 0) ///arriba
        {
            aframe = 14;
            if(framecont < 40) {
                posy -= 2.5;
            }
            if(framecont >= 40) {
                posy += 2.5;
            }
        }
            framecont++;
            if(framecont > 79)
            {
                estado = 1;
                framecont = 0;
                posy = 400;
            }
            break;

        case(6): ///hit
            if(framecont == 0)
            {
                hitbox.x = 600;
                hitbox.y = 600;
                posy = 400;
            }
            aframe = 18;
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
            aframe += 21;
        }
        return aframe;
    }
};

#endif // CLASEJUGADORHARD_H_INCLUDED
