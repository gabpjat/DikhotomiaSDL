#ifndef CLASEROCKET_H_INCLUDED
#define CLASEROCKET_H_INCLUDED

class Rocket: public entidad
{
private:
    bool activo;
    SDL_Rect hitbox;
    float pendiente;
    float mousex;
    float mousey;
    float jposx;
    float jposy;
    float dirx;
    float diry;

public:
    ~Rocket(){}

    void set_hbx(int aux){hitbox.x = aux;}
    void set_hby(int aux){hitbox.y = aux;}
    void set_hbw(int aux){hitbox.w = aux;}
    void set_hbh(int aux){hitbox.h = aux;}
    void set_pend(float aux){pendiente = aux;}
    void set_activo(bool aux){activo = aux;}
    void set_mousex(float aux){mousex = aux;}
    void set_mousey(float aux){mousey = aux;}
    void set_jposx(float aux){jposx = aux;}
    void set_jposy(float aux){jposy = aux;}

    float get_hbx(){return hitbox.x;}
    float get_hby(){return hitbox.y;}
    int get_hbw(){return hitbox.w;}
    int get_hbh(){return hitbox.h;}
    float get_mousex(){return mousex;}
    float get_mousey(){return mousey;}
    float get_jposx(){return jposx;}
    float get_jposy(){return jposy;}
    SDL_Rect get_hitbox(){return hitbox;}
    float get_pend(){return pendiente;}
    bool get_activo(){return activo;}


        void trayectoriaRocket()
            {
                ///pendiente = (mousey - jposy) / (mousex - jposx); ///m = (y2 - y1)/(x2 - x1)

                dirx = mousex - jposx;
                diry = mousey - jposy;
                pendiente = (dirx*dirx) + (diry*diry);
                pendiente = sqrt(pendiente);
                dirx /= pendiente;
                diry /= pendiente;
                dirx *= 8;
                diry *= 8;


                if(mousex > jposx) {
                    orientacion = true;
                }
                else{orientacion = false;}
            }

        void viajeRocket2()
        {
            hitbox.x += 2*dirx;
            hitbox.y += 2*diry;
        }



    Rocket()
        {
            activo = false;
            hitbox.x = -500;
            hitbox.y = -500;
            hitbox.w = 15;
            hitbox.h = 15;
            estado = 0;
            framecont = 0;
            ///la pendiente siempre se define antes de dispararlo
        }

    void definir_frame()
        {
                if(mousex > jposx + 30 && mousey > jposy + 50)
                {
                    aframe = 3;
                }
                else if(mousex > jposx + 30 && mousey < jposy - 50)
                {
                    aframe = 1;
                }
                else if((mousex > jposx + 30 && mousey <= jposy + 50) || (mousex > jposx + 30 && mousey >= jposy - 50))
                {
                    aframe = 2;
                }
                else if(mousex <= jposx -30 && mousey > jposy + 50)
                {
                    aframe = 5;
                }
                else if(mousex <= jposx -30 && mousey < jposy - 50)
                {
                    aframe = 7;
                }
                else if((mousex <= jposx -30 && mousey <= jposy + 50) || (mousex > jposx && mousey >= jposy - 50))
                {
                    aframe = 6;
                }
                else if((mousex >= jposx -30  && mousey > jposy) || (mousex <= jposx +30  && mousey > jposy))
                {
                    aframe = 4;
                }
                else if((mousex >= jposx -30  && mousey < jposy) || (mousex <= jposx +30  && mousey < jposy))
                {
                    aframe = 0;
                }


        }

    void definir_accion(int estado, float posx, float posy, float mousex, float mousey)
        {
        if(framecont == 0 && (estado == 0 || estado == 1 || estado == 2 || estado == 3))
            {


            switch(estado)
            {
                case(0): ///sin disparar
                    activo = false;

                    break;
                case(1): ///disparad
                    framecont++;
                    break;
                case(2): ///explota en el piso solamente
                    activo = false;

                    break;
                case(3): ///explota en un enemigo
                    activo = false;

                    break;
                default:

                    break;
            }
            return;
            }
        }
    void disparar(float posx, float posy, float mousex, float mousey)
        {
            activo = true;
            framecont++;

        }


};


#endif // CLASEROCKET_H_INCLUDED
