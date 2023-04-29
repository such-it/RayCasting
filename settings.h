#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>
#include<math.h>
#define min(a,b)(((a) > (b)) ? (b) : (a))
#define max(a,b)(((a) > (b)) ? (a) : (b))

#define WIDTH 600
#define HEIGHT 450
#define FOV M_PI/3
#define HFOV M_PI/6
#define deltaAngle FOV/600
#define Cell 16
#define Row 25
#define Col 25
#define _ 0

#define LIGHTGRAY  (SDL_Color){ 150, 150, 150, 255 } 
#define DARKGRAY   (SDL_Color){ 50, 50, 50, 255 }    
#define RED        (SDL_Color){ 255, 0, 0, 255 }   
#define GREEN      (SDL_Color){ 0, 255, 0, 255 }    
#define SKYBLUE    (SDL_Color){ 102, 191, 255, 255 } 
#define BLUE       (SDL_Color){ 0, 0, 255, 255 }   
#define WHITE      (SDL_Color){ 255, 255, 255, 255 } 
#define BLACK      (SDL_Color){ 0, 0, 0, 255 }       


typedef signed char i8 ; 
typedef unsigned char ui8 ; 
typedef unsigned long long ui64 ; 

struct _Window_{

    SDL_Window * window ; 
    SDL_Surface * surface ; 
    SDL_Renderer * render ; 

    ui64 end , beg ;
    int deltaTime ;
    bool isOpen ;
}; 
static struct _Window_ Window ; 


typedef struct Vector2i{
    int x;
    int y;
} Vector2i ; 

typedef struct Vector2f{
    float x;
    float y;
} Vector2f ; 

typedef enum Projection {
    dimension_2,
    dimension_3,
    dimension_3_texture,
}Projection;


float RadToDegree(float);
float DegreeToRad(float);
void draw_circle(Vector2f , float , SDL_Color);
void set_color(SDL_Color);


float RadToDegree(float radian)
{
    return ( radian/M_PI)*180.f;
}

float DegreeToRad(float degree)
{
    return ( degree/180.f )*M_PI ; 
}

void set_color(SDL_Color color)
{
    SDL_SetRenderDrawColor(Window.render , color.r , color.g , color.b , color.a);
}

void draw_circle(Vector2f pos , float radius , SDL_Color color)
{
    set_color(color);
    for (short i = 0 ; i < 360 ; i++)
    {
        SDL_RenderDrawLineF(Window.render , pos.x , pos.y , pos.x + radius*cos(DegreeToRad(i)) , pos.y + radius*sin(DegreeToRad(i)));
    }
}


short draw_i_map[25][25] = 
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,_,_,_,1},
    {1,_,_,1,1,1,1,1,1,1,_,_,1,_,_,1,1,1,1,_,_,1,_,_,1},
    {1,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1,_,_,1},
    {1,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1,_,_,1},
    {1,1,1,1,1,1,1,1,1,1,_,_,1,1,1,1,_,_,1,1,1,1,_,_,1},
    {1,_,_,_,_,_,_,_,_,1,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,1,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1},
    {1,_,_,1,1,1,1,_,_,1,1,1,1,_,_,1,1,1,1,_,_,1,1,1,1},
    {1,_,_,_,_,_,1,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,1},
    {1,_,_,_,_,_,1,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,1},
    {1,1,1,1,_,_,1,1,1,1,_,_,1,1,1,1,1,1,1,_,_,1,_,_,1},
    {1,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1},
    {1,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1},
    {1,_,_,1,1,1,1,1,1,1,1,1,1,_,_,1,_,_,1,1,1,1,1,1,1},
    {1,_,_,1,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,1},
    {1,_,_,1,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,_,_,_,1},
    {1,_,_,1,_,_,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,_,_,1},
    {1,_,_,1,_,_,1,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,1},
    {1,_,_,1,_,_,1,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,1},
    {1,_,_,1,_,_,1,1,1,1,_,_,1,1,1,1,_,_,1,_,_,1,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1},
    {1,_,_,_,_,_,_,_,_,_,_,_,1,_,_,_,_,_,1,_,_,_,_,_,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
