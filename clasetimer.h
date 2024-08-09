#ifndef CLASETIMER_H_INCLUDED
#define CLASETIMER_H_INCLUDED

class timer
{
    private:
        int start_ticks;
        int paused_ticks;
        bool paused;
        bool started;
    public:
    ~timer(){}
    timer() {
        start_ticks = 0;
        paused_ticks = 0;
        paused = false;
        started = false;
    }
    void start(){
        started = true;
        paused = false;
        start_ticks = SDL_GetTicks();
    }
    void stop(){
         started = false;
        paused = false;
    }
    void pause(){
        if( ( started == true ) && ( paused == false ) )
        {
            paused = true;
            paused_ticks = SDL_GetTicks() - start_ticks;
        }
    }
    void unpause(){
        if( paused == true )
        {
            paused = false;
            start_ticks = SDL_GetTicks() - paused_ticks;
            paused_ticks = 0;
        }
    }
    int get_ticks(){
        if( started == true )
        {
            if( paused == true )
            {
                return paused_ticks;
            }
            else
            {
                return SDL_GetTicks() - start_ticks;
            }
        }
        return 0;
    }
    bool is_started(){
        return started;
    }
    bool is_paused(){
        return paused;
    }
};
#endif // CLASETIMER_H_INCLUDED
