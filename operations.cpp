#ifndef ELEMENT
#define ELEMENT data[row][col]
#endif

#ifndef ELEMENT_TRANSPOSE
#define ELEMENT_TRANSPOSE data[col][row]
#endif

#include "matrix.cpp"

Matrix transpose(Matrix m)
{
    if(!m.isOkay())
    {
        cout << endl;
        cout << "Hence, we cannot obtain its transpose";
        return Matrix(false);
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();
        int cols = m.getCols();

        float **transpose = getNewArray(cols, rows);

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
                transpose[col][row] = data[row][col];
        }

        return Matrix(transpose, cols, rows);
    }
}