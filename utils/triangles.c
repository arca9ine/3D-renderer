#include <SDL2/SDL.h>
#include <math.h>

#include "hlinalg.h"
#include "randomutils.h"
#include "triangles.h"
#include "camera.h"

#include <stdio.h>

int SetNormal(Triangle *t) {
    Vec diff1, diff2;
    int errors;

    errors += SubVecs(t->v[0], t->v[1], &diff1);
    errors += SubVecs(t->v[0], t->v[2], &diff2);

    Vec normal = CrossProd(diff1, diff2);

    Normalize(&normal);
    t->n = normal;
    return errors;
}

int Perspectivize(Vec v, Camera c, Vec *out) {
    int errors = 0;

    float scale = 1 / tan((c.fov * 3.1415) / 360.0 );

    Matrix m = {.m = {
        {scale, 0.0, 0.0},
        {0.0, scale, 0.0},
        {0.0, 0.0, -(c.end)/(c.end - c.start)}
    }};

    for (int i = 0; i < 3; i++) {
        out->c[i] = v.c[0] * m.m[i][0] + v.c[1] * m.m[i][1] + v.c[2] * m.m[i][2];
    }

    out->c[2] -= 1.0;

    float divisor = -(c.end * c.start * v.c[2])/(c.end - c.start);
    for (int i = 0; i < 3; i++) {
        out->c[i] = out->c[i] / divisor;
    }

    return errors;
}

SDL_Vertex VecToVertex(Vec v, SDL_Color colour) {
    SDL_Vertex out = {
        .position = {.x = v.c[0], .y = v.c[1]},
        .color = colour,
        .tex_coord = {.x = 0, .y = 0}
    };
    return out;
}

int GenerateVertices(Triangle *t, Camera c) {
    int errors = 0;
    Vec transformed;

    float colourScalar = fabs(DotProd(t->n, c.direction));
    SDL_Color shadedColour = {
        .r = (int) (colourScalar * t->colour.r),
        .g = (int) (colourScalar * t->colour.r),
        .b = (int) (colourScalar * t->colour.r),
        };

    for (int i = 0; i < 3; i++) {
        errors += SubVecs(t->v[i], c.origin, &transformed);
        errors += Perspectivize(t->v[i], c, &transformed);

        t->vertices[i] = VecToVertex(transformed, shadedColour);
    }
    return errors;
};

SDL_Vertex ScreenScale(SDL_Vertex v, SDL_Renderer *renderer) {

    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    SDL_Vertex out = {
        .color = v.color,
        .position = {.x = (v.position.x  * (w / 2)) + (w / 2), .y = (v.position.y * (w / 2)) + (h / 2)},
        .tex_coord = v.tex_coord
    };

    return out;
};

int RenderTriangle(SDL_Renderer *renderer, Triangle t, Camera c) {
    int errors = 0;
    GenerateVertices(&t, c);
    SDL_Vertex shiftedVertices[3];
    for (int i = 0; i < 3; i++) {
        shiftedVertices[i] = ScreenScale(t.vertices[i], renderer);
    }
    // change this condition later but rn i dont have a real direction 
    // for the normal vector at the moment
    if (-fabs(DotProd(t.n, c.direction)) < 0.0) {
        errors += SDL_RenderGeometry(renderer, NULL, shiftedVertices, 3, NULL, 0);
    }
    return errors;
};
