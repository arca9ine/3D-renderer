# 3D-renderer
quick sdl2-based 3D renderer in C

## triangles.h:
everything that gets rendered has to be in the form of a Triangle. this file also includes the math to render the triangle to an SDL renderer.

## hlinalg.h:
this implements some super basic linear algebra, quite literally just vector addition lol

## randomutils.h:
this was just for a min function and the fast inverse square (shamelessly stolen from quake) that i didn't want to put into macros
