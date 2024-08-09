#ifndef CLASEOBJETO_H_INCLUDED
#define CLASEOBJETO_H_INCLUDED

class objeto{
protected:
    float posx;
    float posy;
    int estado;
    int width;
    int height;
public:
    float get_posx() {return posx;}
    float get_posy() {return posy;}
    int get_estado() {return estado;}
    int get_width() {return width;}
    int get_height() {return height;}
    void set_posx(float aux) {posx = aux;}
    void set_posy(float aux) {posy = aux;}
    void set_estado(int aux) {estado = aux;}
    void set_width(int aux) {width = aux;}
    void set_height(int aux) {height = aux;}
    objeto() {
        posx = 0;
        posy = 0;
        estado = 0;
        width = 0;
        height = 0;
    }
    ~objeto(){}
};

class entidad: public objeto{
protected:
    int salud;
    int xvel;
    int yvel;
    int aframe;
    int framecont;
    bool orientacion;
    int cooldown;
public:
    int get_salud() {return salud;}
    void set_salud(int aux) {salud = aux;}
    int get_xvel() {return xvel;}
    int get_yvel() {return yvel;}
    void set_xvel(int aux) {xvel = aux;}
    void set_yvel(int aux) {yvel = aux;}
    int get_aframe() {return aframe;}
    int get_framecont() {return framecont;}
    void set_aframe(int aux) {aframe = aux;}
    void set_framecont(int aux) {framecont = aux;}
    bool get_orientacion() {return orientacion;}
    void set_orientacion(bool aux) {orientacion = aux;}
    int get_cooldown() {return cooldown;}
    void set_cooldown(int aux) {cooldown = aux;}

    entidad(){
        salud = 0;
        xvel = 0;
        yvel = 0;
        aframe = 0;
        framecont = 0;
        orientacion = true;
        cooldown = 0;
    }
    ~entidad(){}
};

class pastillas: public objeto{
protected:
    int aframe;
    int cooldown;
    SDL_Rect pickbox;
public:
    int get_aframe(){return aframe;}
    void set_aframe(int aux) {aframe = aux;}
    SDL_Rect get_pickbox() {return pickbox;}
    void set_pickbox(SDL_Rect aux) {pickbox = aux;}
    int get_cooldown() {return cooldown;}
    void set_cooldown(int aux) {cooldown = aux;}
    pastillas() {
        cooldown = 0;
        aframe = 0;
        posx = 200;
        posy = -90;
        estado = 0;
        width = 48;
        height = 48;
        pickbox.h = 48;
        pickbox.w = 48;
        pickbox.x = 200;
        pickbox.y = -90;
    }
    int animar_brut(int frame) {
        if(frame < 15) {
            aframe = 0;
        }
        else if(frame < 45 && frame >= 30) {
            aframe = 2;
        }
        else {
            aframe = 1;
        }
        return aframe;
    }
    int animar_hard(int frame) {
        if(frame < 8) {
            aframe = 0;
        }
        else if(frame < 15 && frame >= 8) {
            aframe = 1;
        }
        else if(frame < 22 && frame >= 15) {
            aframe = 2;
        }
        else if(frame < 29 && frame >= 22) {
            aframe = 3;
        }
        else if(frame < 37 && frame >= 29) {
            aframe = 4;
        }
        else if(frame < 44 && frame >= 37) {
            aframe = 5;
        }
        else if(frame < 51 && frame >= 44) {
            aframe = 6;
        }
        else{
            aframe = 7;
        }
        return aframe;
    }
    void spawn_brut() {
        posx = ((rand() % 800) + 100);
        posy = ((rand() % 240) + 200);
        pickbox.x = posx;
        pickbox.y = posy;
        estado = 1;
    }
    void spawn_hard() {
        posx = ((rand() % 800) + 100);
        posy = ((rand() % 100) + 350);
        pickbox.x = posx;
        pickbox.y = posy;
        estado = 1;
    }
    void despawn() {
        posx = 200;
        posy = -90;
        pickbox.x = posx;
        pickbox.y = posy;
        estado = 0;
        cooldown = 60;
    }
    ~pastillas(){}
};

#endif // CLASEOBJETO_H_INCLUDED
