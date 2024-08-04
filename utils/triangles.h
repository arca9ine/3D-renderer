#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "hlinalg.h"
#include "camera.h"
#include "SDL2/SDL.h"

typedef struct Triangle{
    Vec v[3];
    Vec transformedVecs[3];
    Vec n;
    SDL_Color colour;
    SDL_Vertex vertices[3];
} Triangle;

typedef struct Shape{
    Triangle *triangles;
    Vec position;
    int count;
} Shape;

/*
SetNormal(Triangle *t)
    Takes a triangle and sets the normal vector of the triangle using the vector corners.
    Requires v[] to be populated.
Inputs:
    Triangle *t: the triangle in question
Outputs:
    int: Returns a non-zero value if it fails
*/
int SetNormal(Triangle *t);

/*
Perspectivize(Vec v, Camera c, Vec *out)
    Takes a vector and a camera and projects the vector onto the camera's viewing plane
Inputs:
    Vec v: The original vector
    Camera c: The camera viewing the vector
    Vec *out: The returned vector
Output:
    int: Returns a non-zero value if it fails
*/
int Perspectivize(Vec v, Camera c, Vec *out);

/*
VecToVertex(Vec v, SDL_Color colour)
    Takes a vector and colour and generates an SDL_Vertex with the x and y values and colour.
Inputs:
    Vec v: The vector with the x and y coordinates
    SDL_Color colour: The colour to set the vertex
Output:
    SDL_Vertex: The generated SDL_Vertex
*/
SDL_Vertex VecToVertex(Vec v, SDL_Color colour);

/*
GenerateVertices(Triangle *t, Camera c)
    Takes a triangle and camera to populate the SDL_Vertex[] of the triangle
Inputs:
    Triangle *t: The triangle to populate
    Camera c: The camera to generate the points with respect to
Output:
    int: non-zero if an error is thrown
*/
int GenerateVertices(Triangle *t, Camera c);

/*
RenderTriangle(SDL_Renderer *renderer, Triangle t, Camera c)
    Renders a triangle (with a camera) to a renderer
Inputs:
    SDL_Renderer *renderer: The renderer to publish the triangle to
    Triangle t: The triangle to render on the screen
    Camera c: The camera to take the perspective from
*/
int RenderTriangle(SDL_Renderer *renderer, Triangle t, Camera c);

#endif // TRIANGLES.H