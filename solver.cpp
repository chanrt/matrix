#ifndef SOLVER
#define SOLVER

#include <iostream>
#include "matrix.cpp"
#include "operations.cpp"

using namespace std;

Matrix solveHeterogeneous(Matrix m, Matrix vec)
{
    if (!m.isOkay())
    {
        cout << endl;
        cout << "Hence, we cannot solve it";
    }
    else if (!m.isSquare())
    {
        cout << endl;
        cout << "This is not a square matrix, it cannot be solved";
    }
    else
    {
        Matrix inverse(m.getRows());
        inverse.clone(getInverse(m));

        return (inverse*vec);
    }
    return Matrix(false);
}
#endif