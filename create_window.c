#include "create_window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct {
  float pos_x, pos_y, width, height;

  SDL_Color color;

  int is_active;

  float speed_x, speed_y;


  
} GameObject;

GameObject* create_rect(float pos_x, float pos_y, float width, float height, SDL_Color color){
  GameObject* obj = (GameObject*)malloc(sizeof(GameObject));
  if(!obj) return NULL;
  
  obj->pos_x = pos_x;
  obj->pos_y = pos_y;
  obj->width = width;
  obj->height = height;
  obj->color = color;
  obj->is_active = 1;
  obj->speed_x = 0;
  obj->speed_y = 0;


  return obj;
}

/* void create_rect(SDL_Renderer *renderer, int pos_x, int pos_y){
  SDL_Rect rect;
  rect.x = pos_x;
  rect.y = pos_y;
  rect.w = 100;
  rect.h = 20;
  
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawRect(renderer,&rect);
  SDL_RenderFillRect(renderer, &rect);
 
} */

void create_window(SDL_Window *window, SDL_Renderer *renderer){

  /* int pos_x = 270;
  float pos_y = 10.0f;
  int gravity_y = 2;
  */
  
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
      printf("SDL could not initialize,SDL_Error: %s\n", SDL_GetError());
    } else {
      window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

      renderer = SDL_CreateRenderer(window, -1 , 0);
      float speed = 35.0f;
      Uint64 last_time = SDL_GetTicks64();

      if (window == NULL) {
        printf("Error during window creation,SDL_ERROR: %s\n", SDL_GetError());
      } else {
        int running= 1;
        while (running) {
          SDL_Event e;

          while (SDL_PollEvent(&e)) {
           if(e.type == SDL_QUIT){
             running = 0;
           }
          }

            Uint64 current_time = SDL_GetTicks64();
            float delta_time = (current_time - last_time)/ 1000.0f;
            last_time = current_time;

             //pos_y += speed * delta_time;
            
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            //create_rect(renderer, pos_x, (int)pos_y);

            SDL_RenderPresent(renderer);
            SDL_Delay(16);
          }
        }
      }
    }

