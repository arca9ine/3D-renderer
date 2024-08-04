#include <stdio.h>
#include <assert.h>

#include "utils/hlinalg.h"
#include "utils/randomutils.h"
#include "utils/triangles.h"
#include "utils/camera.h"

void TestDotProd() {
    Vec v1 = {.c = {1.0, 0.0, 4.0, 1.0}};
    Vec v2 = {.c = {2.0, 3.0, 5.0, 1.0}};

    float prod = DotProd(v1, v2);

    printf("\tDot Product: %.2f\n", prod);

    assert(prod == 22.0);
}

void TestCrossProd() {
    Vec v1 = {.c = {1.0, 0.0, 4.0, 1.0}};
    Vec v2 = {.c = {2.0, 3.0, 5.0, 1.0}};
    Vec out = CrossProd(v1, v2);

    printf("\tCross Product: [%.2f, %.2f, %.2f, %.2f]\n", out.c[0], out.c[1], out.c[2], out.c[3]);

    assert(out.c[0] == -12.0);
    assert(out.c[1] == 3.0);
    assert(out.c[2] == 3.0);
}

void TestMatrix() {
    Matrix m = {.m = {
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    }};
    Vec v = {.c = {1.0, 2.0, 3.0, 4.0}};
    Vec out;

    ApplyMatrix(v, m, &out);
    printf("\tAfter Identity: [%.2f, %.2f, %.2f, %.2f]\n", out.c[0], out.c[1], out.c[2], out.c[3]);
    assert(out.c[0] == 1.0);
    assert(out.c[1] == 2.0);
    assert(out.c[2] == 3.0);
    assert(out.c[3] == 4.0);

    m.m[0][3] = 2.0;
    m.m[2][0] = 7.0;
    m.m[2][2] = 0.0;
    ApplyMatrix(v, m, &out);
    printf("\tAfter Matrix 2: [%.2f, %.2f, %.2f, %.2f]\n", out.c[0], out.c[1], out.c[2], out.c[3]);
    assert(out.c[0] == 9.0);
    assert(out.c[1] == 2.0);
    assert(out.c[2] == 7.0);
    assert(out.c[3] == 4.0);
}

void TestNormalize() {
    Vec v = {.c = {3.0, 0.0, 0.0, 1.0}};
    Normalize(&v);
    printf("\tNormalized Vector: [%.2f, %.2f, %.2f, %.2f]\n", v.c[0], v.c[1], v.c[2], v.c[3]);
}

void TestStandardize() {
    Vec v = {.c = {1.0, 0.0, 0.0, 2.0}};
    Standardize(&v);
    printf("\tStandardized Vector: [%.2f, %.2f, %.2f, %.2f]\n", v.c[0], v.c[1], v.c[2], v.c[3]);
}

void TestAddSub() {
    Vec v1 = {.c = {1.0, 1.0, 1.0, 1.0}};
    Vec v2 = {.c = {2.0, -1.0, 3.0, 1.0}};
    Vec out1, out2;
    AddVecs(v1, v2, &out1);
    SubVecs(v1, v2, &out2);
    printf("\tAdded: [%.2f, %.2f, %.2f, %.2f]\n", out1.c[0], out1.c[1], out1.c[2], out1.c[3]);
    printf("\tSubtracted: [%.2f, %.2f, %.2f, %.2f]\n", out2.c[0], out2.c[1], out2.c[2], out2.c[3]);
}

void TestNormal(Triangle t) {
    SetNormal(&t);
    printf("\tNormal:[%.2f, %.2f, %.2f, %.2f]\n", t.n.c[0], t.n.c[1], t.n.c[2], t.n.c[3]);
}

int main(int argc, char **argv) {
    printf("\nhlinalg.c Tests:\n");
    TestDotProd();
    TestCrossProd();
    TestMatrix();
    TestNormalize();
    TestStandardize();
    TestAddSub();
    printf("\ntriangles.c Tests:\n");
    Triangle t = {.v = { {.c = {0.5, 0.0, 0.0, 1.0}}, {.c = {-0.5, 0.0, 0.0, 1.0}}, {.c = {0.0, 0.83, 0.0, 1.0}}}};
    TestNormal(t);
}