#pragma once
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "settings.h"

typedef struct Ray{

    Vector2f length ; 
    Vector2f pos ; 
    Vector2f direction ; 
    Vector2i current_cell ; 
    Vector2i step ; 
    Vector2f deltaDist ; 
    float angle , distance; 

}Ray;

void ray_casting(Ray * , Vector2f , float , short i_map[25][25] , Projection , SDL_Texture * );

void ray_casting(Ray * ray , Vector2f pos , float angle , short i_map[25][25] , Projection projection , SDL_Texture * texture)
{

    ray->pos = pos; 

    ray->angle = angle - HFOV - 0.000001;

    bool falg_offset = false  ;
    int wall_texture = 0  ;

    for (int i = 0 ; i < WIDTH ; i++)
    {
        ray->direction.x = cos(ray->angle);
        ray->direction.y = sin(ray->angle);

        ray->current_cell.x = (int)(ray->pos.x / Cell) ; 
        ray->current_cell.y = (int)(ray->pos.y / Cell) ; 

        ray->deltaDist.x = Cell * sqrt( 1 + pow(ray->direction.y / ray->direction.x , 2) );
        ray->deltaDist.y = Cell * sqrt( 1 + pow(ray->direction.x / ray->direction.y , 2) );

        if (ray->direction.x < 0)
        {
            ray->step.x = -1;
            ray->length.x = ( ray->pos.x / Cell - ray->current_cell.x)*ray->deltaDist.x ; 
        }
        else 
        {
            ray->step.x = 1 ; 
            ray->length.x = (ray->current_cell.x + 1  - ray->pos.x/Cell)*ray->deltaDist.x ; 
        }

        if (ray->direction.y < 0)
        {
            ray->step.y = -1;
            ray->length.y = ( ray->pos.y / Cell - ray->current_cell.y)*ray->deltaDist.y ; 
        }
        else 
        {
            ray->step.y = 1 ; 
            ray->length.y = (ray->current_cell.y + 1  - ray->pos.y/Cell)*ray->deltaDist.y ; 
        }

        for ( bool hit = false ; hit == false && ray->distance < 600.f ; )
        {
            if ( ray->length.x < ray->length.y )
            {
                ray->distance = ray->length.x ; 
                ray->current_cell.x += ray->step.x ; 
                ray->length.x += ray->deltaDist.x ; 
                falg_offset = true; 
            }
            else 
            {
                ray->distance = ray->length.y ; 
                ray->current_cell.y += ray->step.y ; 
                ray->length.y += ray->deltaDist.y ;
                falg_offset = false ;
            }

            if (0 <= ray->current_cell.x && ray->current_cell.x < Col && 0 <= ray->current_cell.y && ray->current_cell.y < Row)
            {
                if ( i_map[ray->current_cell.y][ray->current_cell.x] == 1 )
                {
                    hit = true ; 
                }
            }       
        }

        ray->distance = min(ray->distance , 600.f);
        ray->angle += deltaAngle;


        switch(projection)
        {
            case dimension_2 : 
            {
                set_color(BLUE);
                SDL_RenderDrawLineF(Window.render , ray->pos.x , ray->pos.y , ray->pos.x + (ray->distance * ray->direction.x) , ray->pos.y + (ray->distance * ray->direction.y));
                break ; 
            }
            case dimension_3 :
            {

                ray->distance = ray->distance*cos( angle - ray->angle);
                float height = ((HEIGHT*2/tan(HFOV)) / (ray->distance + 0.0001))*3 ; 

                ui8 c = max(min( 150 , 255/(1 + ray->distance * 0.08)) , 50) ; 
                SDL_SetRenderDrawColor(Window.render , c , c , c , 255);
                
                SDL_RenderFillRectF(Window.render , &(SDL_FRect){i ,  HEIGHT/2 - (height/2) , 1 , height });
                break;
            }   
            case dimension_3_texture : 
            {

                if (falg_offset == true)
                {
                    wall_texture = (ray->pos.y + ray->distance * ray->direction.y) - Cell * floor(( ray->pos.y + ray->distance * ray->direction.y)/Cell);
                }
                else 
                {
                    wall_texture = Cell * ceil((ray->pos.x + ray->distance * ray->direction.x)/Cell) - (ray->pos.x + ray->distance * ray->direction.x) ; 
                }
                 
                ray->distance = ray->distance*cos( angle - ray->angle);
                float height = ((HEIGHT*2/tan(HFOV)) / (ray->distance + 0.0001))*3 ; 

                SDL_RenderCopy(Window.render , texture , &(SDL_Rect){wall_texture,0,1,16} , &(SDL_Rect){i,HEIGHT/2 - (height/2),1,height});
                break; 
            }

        }

    }

}
