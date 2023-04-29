#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<math.h>

#include "settings.h"
#include "player.h"
#include "raycasting.h"

struct Manager{
    Player player ; 
    SDL_Texture * numeric ;     
    SDL_Texture * texture ; 
    Ray ray ; 
    short i_map[25][25] , pressed_timer ;
    Projection projection ; 
} manager; 


void InitWindow(const char * );
void draw();
void update();
void QuitWindow();


void InitWindow(const char * title)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(false);

    Window.window = SDL_CreateWindow(title , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 600 , 450 , 0);
    Window.surface = SDL_GetWindowSurface(Window.window);
    Window.render = SDL_CreateRenderer(Window.window , -1 , SDL_RENDERER_ACCELERATED);
    Window.isOpen = true ; 

    Window.beg = 0 ; 
    Window.end = 0 ;
    Window.deltaTime = 0 ;

    InitPlayer(&manager.player,  (Vector2f){80,80});


    SDL_Surface * surface = IMG_Load("img/numeric.png") ; 
    manager.numeric = SDL_CreateTextureFromSurface(Window.render , surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("img/wall.png");
    manager.texture = SDL_CreateTextureFromSurface(Window.render , surface);
    SDL_FreeSurface(surface);

    manager.projection = dimension_3_texture;
    manager.pressed_timer = 20 ; 

    for (i8 y = 0 ; y < Col ; y++)
    {
        for (i8 x = 0 ; x < Row ; x++)
        {
            manager.i_map[y][x] = draw_i_map[y][x];
        }
    }
    
}

void draw()
{
    set_color(SKYBLUE);
    SDL_RenderClear(Window.render);

    switch(manager.projection)
    {
        case dimension_2 : 
        {
            for (i8 y = 0 ; y < Row ; y++)
            {
                for (i8 x = 0 ; x < Col ; x++)
                {
                    if (manager.i_map[y][x] == 1)
                    {
                        set_color(DARKGRAY);
                        SDL_RenderFillRectF(Window.render , &(SDL_FRect){x*Cell +1 ,y*Cell +1,Cell-1,Cell-1});
                    }
                    else 
                    {
                        set_color(LIGHTGRAY);
                        SDL_RenderFillRectF(Window.render , &(SDL_FRect){x*Cell +1 ,y*Cell +1,Cell-1,Cell-1});
                    }
                }
            }

            drawPlayer_2d(&manager.player);
            ray_casting(&manager.ray , (Vector2f){manager.player.pos.x + 8 , manager.player.pos.y + 8} , manager.player.angle , manager.i_map , manager.projection , manager.texture);
            
            break ; 
        }   
        case dimension_3 : 
        case dimension_3_texture : 
        {
            set_color(GREEN);
            SDL_RenderFillRectF(Window.render , &(SDL_FRect){0,HEIGHT/2,WIDTH,HEIGHT/2});
            ray_casting(&manager.ray , (Vector2f){manager.player.pos.x + 8 , manager.player.pos.y + 8} , manager.player.angle , manager.i_map , manager.projection , manager.texture);
            break ; 
        }
    }

    int fps = (int)((1000.0f/Window.deltaTime));
    set_color(BLACK);
    SDL_RenderCopy(Window.render , manager.numeric,  &(SDL_Rect){32*(fps/10) , 0 , 32 , 32} , &(SDL_Rect) {16 , 10 , 16,16});
    SDL_RenderCopy(Window.render , manager.numeric,  &(SDL_Rect){32*(fps%10) , 0 , 32 , 32} , &(SDL_Rect) {32 , 10 , 16,16});

    SDL_RenderPresent(Window.render);
    
}

void update()
{
    updatePlayer(&manager.player);
    
    unsigned int button = SDL_GetMouseState(NULL , NULL);
    if ( (button & 4) == 4 && manager.pressed_timer == 0)
    {
        switch(manager.projection)
        {
            case dimension_2 : manager.projection = dimension_3 ; break ; 
            case dimension_3 : manager.projection = dimension_3_texture ; break ; 
            case dimension_3_texture : manager.projection = dimension_2 ; break ; 
        }
        manager.pressed_timer = 20 ; 
    }
    else 
    {
        manager.pressed_timer = max(0, --manager.pressed_timer);
    }
    
}

void QuitWindow()
{
    SDL_DestroyTexture(manager.numeric);
    SDL_DestroyTexture(manager.texture);

    SDL_FreeSurface(Window.surface);
    SDL_DestroyRenderer(Window.render);
    SDL_DestroyWindow(Window.window);    

    SDL_Quit();
}
