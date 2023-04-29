#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<math.h>

#include "settings.h"

typedef struct Player{
    Vector2f pos ; 
    Vector2i mouse ;
    const ui8 * key ;
    i8 direction ; 
    float accleration;
    float angle ;
}Player;


void InitPlayer(Player * , Vector2f );
void drawPlayer_2d(Player *);
void updatePlayer(Player *);
void QuitPlayer(Player * );
bool check(float , float);

void InitPlayer(Player * player , Vector2f pos)
{
    player->pos = pos; 
    player->accleration = 0.f ; 
    player->angle = 0.f ; 
    player->mouse = (Vector2i){0,0};
}

void updatePlayer(Player * player)
{
    /*mouse control*/
    SDL_GetMouseState(&player->mouse.x , &player->mouse.y);
    
    float rot_angle =  (float)((WIDTH/2) - player->mouse.x)/WIDTH ; 

    player->angle -= rot_angle*FOV*0.45 ; 
    player->angle = fmodf(player->angle , 2*M_PI);

    SDL_WarpMouseInWindow(Window.window , WIDTH/2 , HEIGHT/2);


    bool isKeyPressed = false ; 
    player->key = SDL_GetKeyboardState(NULL);

    if (player->key[SDL_SCANCODE_LEFT] == true)
    {
        player->angle -= DegreeToRad(1);
    }
    if (player->key[SDL_SCANCODE_RIGHT] == true)
    {
        player->angle += DegreeToRad(1); 
    }


    if (player->key[SDL_SCANCODE_UP] == true || player->key[SDL_SCANCODE_W] == true)
    {
        isKeyPressed = true ;
        player->direction = 0 ; 
    }
    else if (player->key[SDL_SCANCODE_DOWN] == true || player->key[SDL_SCANCODE_S] == true)
    {
        isKeyPressed = true ; 
        player->direction = 1 ;
    }

    if (isKeyPressed == true)
    {
        player->accleration = min( 1.5 , (player->accleration += 0.35) );
    }
    else 
    {
        player->accleration = max( 0 , (player->accleration -= 0.04) );
    }

    Vector2f new_pos = (Vector2f){0 , 0}; 

    new_pos.x = player->accleration*cos(player->angle)*Window.deltaTime/15;
    new_pos.y = player->accleration*sin(player->angle)*Window.deltaTime/15;

    switch(player->direction)
    {
        case 0 : 
        {
            if ( check( (player->pos.x + new_pos.x )/ Cell , player->pos.y / Cell ) == false )
            {
                player->pos.x += new_pos.x ; 
            }
            if ( check( player->pos.x/Cell , (player->pos.y + new_pos.y)/ Cell ) == false )
            {
                player->pos.y += new_pos.y ; 
            }
            break ; 
        }
        case 1 : 
        {       
            if ( check( (player->pos.x - new_pos.x)/ Cell , player->pos.y / Cell) == false  )
            {
                player->pos.x -= new_pos.x ; 
            }
            if ( check( player->pos.x / Cell , (player->pos.y - new_pos.y)/ Cell  ) == false )
            {
                player->pos.y -= new_pos.y ; 
            }
            break ; 
        }
    }


}

void drawPlayer_2d(Player * player)
{
    draw_circle( (Vector2f){player->pos.x + 8 , player->pos.y + 8} , 7.5 , RED);
    set_color(BLACK);
    SDL_RenderDrawLineF(Window.render , player->pos.x + 8 , player->pos.y + 8 , player->pos.x + 8 + 25*cos(player->angle) , player->pos.y + 8 + 25*sin(player->angle));
}

bool check(float x , float y)
{
    for ( int i = 0 ; i < 4 ; i++ )
    {
        float _x , _y ; 

        switch(i)
        {
            case 0 : 
                _x = floor(x);
                _y = floor(y);
                break ; 
            case 1 : 
                _x = floor(x);
                _y = ceil(y);
                break ;
            case 2 : 
                _x = ceil(x);
                _y = floor(y);
                break ;
            case 3 : 
                _x = ceil(x);
                _y = ceil(y);
                break ;
        }

        if ( draw_i_map[ (int)_y ][ (int)_x ] == 1)
        {
            return true ;    
        }
    }
    return false ;
}