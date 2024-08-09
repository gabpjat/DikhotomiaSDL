#ifndef CLASERANKING_H_INCLUDED
#define CLASERANKING_H_INCLUDED

class ranking{
protected:
    int puntaje;
    int segundos;
    int muertes;
    char nombre[20];
public:
    ~ranking(){}
    int get_puntaje(){return puntaje;}
    int get_segundos(){return segundos;}
    int get_muertes(){return muertes;}
    char* get_nombre(){return nombre;}
    void set_puntaje (int aux) {puntaje = aux;}
    void set_segundos (int aux) {segundos = aux;}
    void set_muertes (int aux) {muertes = aux;}
    void set_nombre (char aux[20]) {strcpy(nombre, aux);}
    ranking() {
        puntaje = 0;
        segundos = 0;
        muertes = 0;
        nombre[0] = '\0';
    }
    bool guardar(const char direccion[50]) {
        FILE *P;
        P = fopen(direccion, "ab");
        if(P == NULL) {
            return false;
        }
        if(fwrite(this, sizeof(*this), 1, P) == 0) {
            return false;
        }
        fclose(P);
        return true;
    }
    bool cargar(int pos) {
        FILE *P;
        P = fopen("rankings\\BRUT.bin", "rb");
        if(P == NULL) {
            return false;
        }
        fseek(P, sizeof(*this), pos);
        if(fread(this, sizeof(*this), 1, P) == 0) {
            return false;
        }
        fclose(P);
        return true;
    }
        void ingresar_nombre(SDL_Surface* fondo) {
        int i = 0;
        strcpy(nombre, "                   ");
        SDL_Surface* name = NULL;
        SDL_Surface* inserte = TTF_RenderText_Solid(font, "Introduzca su nombre: ", text_color);
        SDL_Rect offseti, offsetn;
        offseti.x = 180;
        offseti.y = 320;
        offsetn.x = 500;
        offsetn.y = 320;
        while (i<19) {
            name = TTF_RenderText_Solid(font, nombre, text_color);

            while(SDL_PollEvent(&evento)) {
                if(evento.type == SDL_KEYDOWN) {
                    switch(evento.key.keysym.sym) {
                    case(SDLK_BACKSPACE):
                        if(i != 0) {
                            i--;
                            nombre[i] = ' ';
                        }
                        break;
                    case(SDLK_q):
                        nombre[i] = 'Q';
                        i++;
                        break;
                    case(SDLK_w):
                        nombre[i] = 'W';
                        i++;
                        break;
                    case(SDLK_e):
                        nombre[i] = 'E';
                        i++;
                        break;
                    case(SDLK_r):
                        nombre[i] = 'R';
                        i++;
                        break;
                    case(SDLK_t):
                        nombre[i] = 'T';
                        i++;
                        break;
                    case(SDLK_y):
                        nombre[i] = 'Y';
                        i++;
                        break;
                    case(SDLK_u):
                        nombre[i] = 'U';
                        i++;
                        break;
                    case(SDLK_i):
                        nombre[i] = 'I';
                        i++;
                        break;
                    case(SDLK_o):
                        nombre[i] = 'O';
                        i++;
                        break;
                    case(SDLK_p):
                        nombre[i] = 'P';
                        i++;
                        break;
                    case(SDLK_a):
                        nombre[i] = 'A';
                        i++;
                        break;
                    case(SDLK_s):
                        nombre[i] = 'S';
                        i++;
                        break;
                    case(SDLK_d):
                        nombre[i] = 'D';
                        i++;
                        break;
                    case(SDLK_f):
                        nombre[i] = 'F';
                        i++;
                        break;
                    case(SDLK_g):
                        nombre[i] = 'G';
                        i++;
                        break;
                    case(SDLK_h):
                        nombre[i] = 'H';
                        i++;
                        break;
                    case(SDLK_j):
                        nombre[i] = 'J';
                        i++;
                        break;
                    case(SDLK_k):
                        nombre[i] = 'K';
                        i++;
                        break;
                    case(SDLK_l):
                        nombre[i] = 'L';
                        i++;
                        break;
                    case(SDLK_z):
                        nombre[i] = 'Z';
                        i++;
                        break;
                    case(SDLK_x):
                        nombre[i] = 'X';
                        i++;
                        break;
                    case(SDLK_c):
                        nombre[i] = 'C';
                        i++;
                        break;
                    case(SDLK_v):
                        nombre[i] = 'V';
                        i++;
                        break;
                    case(SDLK_b):
                        nombre[i] = 'B';
                        i++;
                        break;
                    case(SDLK_n):
                        nombre[i] = 'N';
                        i++;
                        break;
                    case(SDLK_m):
                        nombre[i] = 'M';
                        i++;
                        break;
                    case(SDLK_0):
                        nombre[i] = '0';
                        i++;
                        break;
                    case(SDLK_1):
                        nombre[i] = '1';
                        i++;
                        break;
                    case(SDLK_2):
                        nombre[i] = '2';
                        i++;
                        break;
                    case(SDLK_3):
                        nombre[i] = '3';
                        break;
                    case(SDLK_4):
                        nombre[i] = '4';
                        i++;
                        break;
                    case(SDLK_5):
                        nombre[i] = '5';
                        i++;
                        break;
                    case(SDLK_6):
                        nombre[i] = '6';
                        i++;
                        break;
                    case(SDLK_7):
                        nombre[i] = '7';
                        i++;
                        break;
                    case(SDLK_8):
                        nombre[i] = '8';
                        i++;
                        break;
                    case(SDLK_9):
                        nombre[i] = '9';
                        i++;
                        break;
                    case(SDLK_RETURN):
                        nombre[i] = '\0';
                        i = 25;
                        break;
                    default:
                        break;
                    }
                }
            }
            if(i == 19) {
                nombre[19] = '\0';
            }
            SDL_BlitSurface(fondo, NULL, screen, NULL);
            SDL_BlitSurface(inserte, NULL, screen, &offseti);
            SDL_BlitSurface(name, NULL, screen, &offsetn);
            SDL_Flip(screen);
            SDL_FreeSurface(name);
        }
        SDL_FreeSurface(inserte);
    }
};

#endif // CLASERANKING_H_INCLUDED
