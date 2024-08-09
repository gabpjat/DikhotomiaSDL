#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

class objeto{
protected:
    int posx;
    int posy;
    int salud;
    int estado;
public:
    int get_posx() {return posx;}
    int get_posy() {return posy;}
    int get_salud() {return salud;}
    int get_estado() {return estado;}
    void set_posx(int aux) {posx = aux;}
    void set_posy(int aux) {posy = aux;}
    void set_salud(int aux) {salud = aux;}
    void set_estado(int aux) {estado = aux;}
};

class jugador:objeto{
protected:
    int puntaje;
    char nombre[20];
public:
    int get_puntaje() {return puntaje;}
    char *get_nombre() {return nombre;}
    void set_puntaje(int aux) {puntaje = aux;}
    void set_nombre(char aux[20]) {strcpy(nombre, aux);}
};

//The button
class Button
{
    private:
    //The attributes of the button
    SDL_Rect box;

    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;

    public:
    //Initialize the variables
    Button( int x, int y, int w, int h );

    //Handles events and set the button's sprite region
    void handle_events();

    //Shows the button on the screen
    void show(SDL_Surface *);

    public:

    int getbuttonx(){return box.x;}
    int getbuttony(){return box.y;}
    int getbuttonw(){return box.w;}
    int getbuttonh(){return box.h;}

};

#endif // CLASES_H_INCLUDED
