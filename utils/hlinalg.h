#ifndef HLINALG_H
#define HLINALG_H

typedef struct Vec {
    float c[3];
} Vec;

typedef struct Matrix{
    float m[4][4];
} Matrix;

int AddVecs(Vec v1, Vec v2, Vec *out);
int SubVecs(Vec v1, Vec v2, Vec *out);
int ApplyMatrix(Vec v, Matrix m, Vec *out);
int Standardize(Vec *v);
int Normalize(Vec *v);
float DotProd(Vec v1, Vec v2);
Vec CrossProd(Vec v1, Vec v2);

#endif // HLINALG.H