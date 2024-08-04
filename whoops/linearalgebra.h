typedef struct {
    int size;
    float *data;
} Vector;

typedef struct {
    int rows;
    int cols;
    float **array;
} Matrix;

// simple vector operations
int AddVectors(Vector v1, Vector v2, Vector *out);
int SubtractVectors(Vector v1, Vector v2, Vector *out);
Vector ScalarMultiple(Vector v, float f);
Vector ScalarMultipleH(Vector v, float f);
float GetSquareLength(Vector v);
int DotProduct(Vector v1, Vector v2, float *out);


// simple matrix operations
int ApplyMatrix(Vector v, Matrix m, Vector *out);
int ComposeMatrices(Matrix left, Matrix right, Matrix *out);
float GetDeterminant(Matrix m);

// homogenized shtuff
int CrossProduct3Dish(Vector v1, Vector v2, Vector *out);
int Get3DNormal(Vector v1, Vector v2, Vector v3, Vector *out);