#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "settings.h"
#include "main.h"


int SDL_main(int argv , char * argc[])
{
    InitWindow("Ray Casting");
    
    Window.end = SDL_GetTicks64();

    while( Window.isOpen == true )
    {
        Window.beg = SDL_GetTicks64();
        Window.deltaTime = Window.beg - Window.end ; 

        for ( SDL_Event event ; SDL_PollEvent(&event) ; )
        {
            if ( event.type == SDL_QUIT )
            {
                Window.isOpen = false ; 
                break ; 
            }
        }
    
        update();
        draw();
        SDL_Delay(1000/60);

        Window.end = Window.beg ; 
    }
    
    QuitWindow();

    return 0 ; 
}