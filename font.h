#ifndef FONT_H
#define FONT_H

#include "SDL2/SDL.h"

void draw_char(SDL_Renderer *renderer, int x, int y, char c, int scale, SDL_Color color);
void draw_string(SDL_Renderer *renderer, int x, int y, const char *text, int scale, SDL_Color color);
int get_string_width(const char *text, int scale);

#endif // FONT_H
