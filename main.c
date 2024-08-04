#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#include "utils/hlinalg.h"
#include "utils/triangles.h"
#include "utils/camera.h"
#include "utils/randomutils.h"
 
int main(int argc, char** argv) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL failed to initialize. Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Rect screenRect;
    if (SDL_GetDisplayBounds(0, &screenRect)) {
        printf("SDL Failed to read screen dimensions. Error: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(
        "hi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        screenRect.w / 2, screenRect.h / 2, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


    Camera c = {
        .origin = {.c = {0.0, 0.0, 0.0}},
        // .direction = {.c = {-FastInverseRoot(3), -FastInverseRoot(3), -FastInverseRoot(3), 1.0}},
        .direction = {.c = {0.0, 0.0, 1.0}},
        .start = 1.0,
        .end = 50.0,
        .fov = 90
    };

    Triangle t = {
        .v = {
            { .c = {0.0, 8.6, 10.0} },
            { .c = {-5.0, 0.0, 10.0} },
            { .c = {5.0, 0.0, 10.0} }
        },
        .colour = { .r = 255, .g = 255, .b = 255 }
    };

    SetNormal(&t);
    RenderTriangle(renderer, t, c);

    SDL_RenderPresent(renderer);

    // keep it open for a bit
    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

}