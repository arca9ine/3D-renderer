#include "linearalgebra.h"
#include "utils/randomutils.h"

int AddVectors(Vector v1, Vector v2, Vector *out) {
    if (v1.size != v2.size) {
        return -1;
    }
    float a[v1.size];
    for (int i = 0; i < v1.size; i++) {
        a[i] = v1.data[i] + v2.data[i];
    }
    out->size = v1.size;
    out->data = a;
    return 0;
}

int SubtractVectors(Vector v1, Vector v2, Vector *out) {
    if (v1.size != v2.size) {
        return -1;
    }
    float a[v1.size];
    for (int i = 0; i < v1.size; i++) {
        a[i] = v1.data[i] - v2.data[i];
    }
    out->size = v1.size;
    out->data = a;
    return 0;
}

Vector ScalarMultiple(Vector v, float f) {
    for (int i = 0; i < v.size; i++) {
        v.data[i] = v.data[i] * f;
    }
}

Vector ScalarMultipleH(Vector v, float f) {
    // for homogenized coordinates
    for (int i = 0; i < 3; i++) {
        v.data[i] = v.data[i] * f;
    }
}

float GetSquareLength(Vector v) {
    float out = 0.0;
    for (int i = 0; i < v.size; i++) {
        out += v.data[i] * v.data[i];
    }
}

int DotProduct(Vector v1, Vector v2, float *out) {
    // check compatibility
    if (v1.size != v2.size) {
        return -1;
    }

    *out = 0.0;
    for (int i = 0; i < v1.size; i++) {
        *out += v1.data[i] * v2.data[i];
    }
    return 0;
}

int ApplyMatrix(Vector v, Matrix m, Vector *out) {

    // check compatibility
    if (v.size != m.cols) {
        return -1;
    }

    float a[m.rows];

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            a[i] += m.array[i][j] * v.data[j];
        }
    }
    
    out->data = a;
    out->size = m.rows;
    return 0;
}

int ComposeMatrices(Matrix left, Matrix right, Matrix *out) {

    // check compatibility
    if (left.cols != right.rows) {
        return -1;
    }

    out->rows = left.rows;
    out->cols = right.cols;
    float outArray[out->rows][out->cols];
    out->array = outArray;

    for (int i = 0; i < left.rows; i++) {
        for (int j = 0; j < right.cols; j++) {
            out->array[i][j] = 0;
            for (int k = 0; k < left.cols; k++) {
                out->array[i][j] += left.array[i][k] * right.array[k][j];
            }
        }
    }

    return 0;
}

float GetDeterminant(Matrix m) {
    int size = min(m.cols, m.rows);
    float out = 0.0;
    for (int i = 0; i < size; i++) {
        out += m.array[i][i];
    }
    return out;
}

int CrossProduct3Dish(Vector v1, Vector v2, Vector *out) {
    // ok ill be honest it returns a homogenized vector so it has a w component

    if (v1.size < 3 || v2.size < 3) {
        return -1;
    }

    out->size = 4;
    float arrayOut[4] = {
        v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1],
        v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2],
        v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0], 1.0};
    out->data = arrayOut;
}

int Get3DNormal(Vector v1, Vector v2, Vector v3, Vector *out) {
    Vector diff1, diff2;
    int errors = 0;
    errors += SubtractVectors(v1, v2, &diff1);
    errors += SubtractVectors(v1, v3, &diff2);
    errors += CrossProduct3Dish(diff1, diff2, out);
    *out = ScalarMultipleH(*out, FastInverseRoot(GetSquareLength(*out)));
    return errors;
}