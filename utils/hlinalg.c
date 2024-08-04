#include "hlinalg.h"
#include "randomutils.h"

int AddVecs(Vec v1, Vec v2, Vec *out) {
    for (int i = 0; i < 3; i++) {
        out->c[i] = v1.c[i] + v2.c[i];    
    }
    return 0;
}

int SubVecs(Vec v1, Vec v2, Vec *out) {
    for (int i = 0; i < 3; i++) {
        out->c[i] = v1.c[i] - v2.c[i];    
    }
    return 0;
}

int Normalize(Vec *v) {
    float l = 0.0;
    for (int i = 0; i < 3; i++) {
        l += v->c[i] * v->c[i];
    }
    float s = FastInverseRoot(l);
    for (int i = 0; i < 3; i++) {
        v->c[i] = v->c[i] * s;
    }
}

float DotProd(Vec v1, Vec v2) {
    float out = 0.0;
    for (int i = 0; i < 3; i++) {
        out += v1.c[i] * v2.c[i];
    }
    return out;
}

Vec CrossProd(Vec v1, Vec v2) {
    Vec out = {
        .c = {
            v1.c[1] * v2.c[2] - v1.c[2] * v2.c[1],
            v1.c[2] * v2.c[0] - v1.c[0] * v2.c[2],
            v1.c[0] * v2.c[1] - v1.c[1] * v2.c[0]
        }
    };
    return out;
}