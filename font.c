#include "font.h"
#include <stddef.h>

// Simple 5x4 Font (Height 5, Width 4)
// 1 = pixel, 0 = empty
const uint8_t font_A[] = {0x6, 0x9, 0xF, 0x9, 0x9};
const uint8_t font_B[] = {0xE, 0x9, 0xE, 0x9, 0xE};
const uint8_t font_C[] = {0x6, 0x9, 0x8, 0x9, 0x6};
const uint8_t font_D[] = {0xE, 0x9, 0x9, 0x9, 0xE};
const uint8_t font_E[] = {0xF, 0x8, 0xE, 0x8, 0xF};
const uint8_t font_F[] = {0xF, 0x8, 0xE, 0x8, 0x8};
const uint8_t font_G[] = {0x6, 0x8, 0xB, 0x9, 0x6};
const uint8_t font_H[] = {0x9, 0x9, 0xF, 0x9, 0x9};
const uint8_t font_I[] = {0xE, 0x4, 0x4, 0x4, 0xE};
const uint8_t font_J[] = {0x7, 0x2, 0x2, 0xA, 0x4};
const uint8_t font_K[] = {0x9, 0xA, 0xC, 0xA, 0x9};
const uint8_t font_L[] = {0x8, 0x8, 0x8, 0x8, 0xF};
const uint8_t font_M[] = {0x9, 0xF, 0xF, 0x9, 0x9}; 
const uint8_t font_N[] = {0x9, 0xD, 0xB, 0x9, 0x9};
const uint8_t font_O[] = {0x6, 0x9, 0x9, 0x9, 0x6};
const uint8_t font_P[] = {0xE, 0x9, 0xE, 0x8, 0x8};
const uint8_t font_Q[] = {0x6, 0x9, 0x9, 0xA, 0x5};
const uint8_t font_R[] = {0xE, 0x9, 0xE, 0xA, 0x9};
const uint8_t font_S[] = {0x7, 0x8, 0x6, 0x1, 0xE};
const uint8_t font_T[] = {0xF, 0x4, 0x4, 0x4, 0x4};
const uint8_t font_U[] = {0x9, 0x9, 0x9, 0x9, 0x6};
const uint8_t font_V[] = {0x9, 0x9, 0x9, 0x9, 0x6}; // Same as U for simplicity
const uint8_t font_W[] = {0x9, 0x9, 0xF, 0xF, 0x9};
const uint8_t font_X[] = {0x9, 0x9, 0x6, 0x9, 0x9};
const uint8_t font_Y[] = {0x9, 0x9, 0x6, 0x4, 0x4};
const uint8_t font_Z[] = {0xF, 0x1, 0x6, 0x8, 0xF};

const uint8_t font_0[] = {0x6, 0x9, 0x9, 0x9, 0x6};
const uint8_t font_1[] = {0x4, 0xC, 0x4, 0x4, 0xE};
const uint8_t font_2[] = {0xE, 0x1, 0x6, 0x8, 0xF};
const uint8_t font_3[] = {0xE, 0x1, 0x6, 0x1, 0xE};
const uint8_t font_4[] = {0x9, 0x9, 0xF, 0x1, 0x1};
const uint8_t font_5[] = {0xF, 0x8, 0xE, 0x1, 0xE};
const uint8_t font_6[] = {0x6, 0x8, 0xE, 0x9, 0x6};
const uint8_t font_7[] = {0xF, 0x1, 0x2, 0x4, 0x4};
const uint8_t font_8[] = {0x6, 0x9, 0x6, 0x9, 0x6};
const uint8_t font_9[] = {0x6, 0x9, 0x7, 0x1, 0x6};

const uint8_t* get_char(char c) {
    if (c >= 'a' && c <= 'z') c -= 32; // To upper
    switch(c) {
        case 'A': return font_A;
        case 'B': return font_B;
        case 'C': return font_C;
        case 'D': return font_D;
        case 'E': return font_E;
        case 'F': return font_F;
        case 'G': return font_G;
        case 'H': return font_H;
        case 'I': return font_I;
        case 'J': return font_J;
        case 'K': return font_K;
        case 'L': return font_L;
        case 'M': return font_M;
        case 'N': return font_N;
        case 'O': return font_O;
        case 'P': return font_P;
        case 'Q': return font_Q;
        case 'R': return font_R;
        case 'S': return font_S;
        case 'T': return font_T;
        case 'U': return font_U;
        case 'V': return font_V;
        case 'W': return font_W;
        case 'X': return font_X;
        case 'Y': return font_Y;
        case 'Z': return font_Z;
        case '0': return font_0;
        case '1': return font_1;
        case '2': return font_2;
        case '3': return font_3;
        case '4': return font_4;
        case '5': return font_5;
        case '6': return font_6;
        case '7': return font_7;
        case '8': return font_8;
        case '9': return font_9;
        default: return NULL;
    }
}

void draw_char(SDL_Renderer *renderer, int x, int y, char c, int scale, SDL_Color color) {
    const uint8_t* bitmap = get_char(c);
    if (!bitmap) return;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
    for (int i = 0; i < 5; i++) {
        int row = bitmap[i];
        for (int j = 0; j < 4; j++) {
            if ((row >> (3-j)) & 1) {
                SDL_Rect rect = {x + j * scale, y + i * scale, scale, scale};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void draw_string(SDL_Renderer *renderer, int x, int y, const char *text, int scale, SDL_Color color) {
    int cur_x = x;
    while (*text) {
        if (*text == ' ') {
            cur_x += 4 * scale;
        } else {
            draw_char(renderer, cur_x, y, *text, scale, color);
            cur_x += 5 * scale; // 4 width + 1 spacing
        }
        text++;
    }
}
