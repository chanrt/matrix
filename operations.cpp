#ifndef ELEMENT
#define ELEMENT data[row][col]
#endif

#ifndef ELEMENT_TRANSPOSE
#define ELEMENT_TRANSPOSE data[col][row]
#endif

#ifndef OPERATIONS
#define OPERATIONS

#include "matrix.cpp"

Matrix transpose(Matrix m)
{
    if (!m.isOkay())
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

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
                transpose[col][row] = data[row][col];
        }

        return Matrix(transpose, cols, rows);
    }
}

void eliminate(Matrix m)
{
    if (!m.isOkay())
    {
        cout << endl;
        cout << "Hence, we cannot apply elimination on it";
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();
        int cols = m.getCols();
        bool row_to_exchange;

        for (int row = 0; row < rows - 1; row++)
        {
            if (data[row][row] == 0)
            {
                row_to_exchange = true;
                for (int new_row = row + 1; new_row < rows; new_row++)
                {
                    if (data[new_row][row] != 0)
                    {
                        m.rowExchange(new_row, row);
                        row_to_exchange = false;
                        break;
                    }
                }
                if (row_to_exchange) // elimination failed
                    break;
            }

            for (int i = row + 1; i < rows; i++)
                m.rowAdd(i, row, data[row][row], -data[i][row]);
        }
    }
}

void triangulate(Matrix m, Matrix identity)
{
    if (!m.isOkay())
    {
        cout << endl;
        cout << "Hence, we cannot apply elimination on it";
    }
    else if (!m.isSquare())
    {
        cout << endl;
        cout << "Triangulation can be done only for square matrices";
    }
    else
    {
        float **data = m.getData();
        float **identity_data = identity.getData();

        int rows = m.getRows();
        int cols = m.getCols();
        bool row_to_exchange;

        for (int row = 0; row < rows - 1; row++)
        {
            if (data[row][row] == 0)
            {
                row_to_exchange = true;
                for (int new_row = row + 1; new_row < rows; new_row++)
                {
                    if (data[new_row][row] != 0)
                    {
                        m.rowExchange(new_row, row);
                        identity.rowExchange(new_row, row);
                        row_to_exchange = false;
                        break;
                    }
                }
                if (row_to_exchange) // elimination failed
                    break;
            }

            for (int i = row + 1; i < rows; i++)
            {
                identity.setElement(i, row, data[i][row] / data[row][row]);
                m.rowAdd(i, row, data[row][row], -data[i][row]);

                m.display();
                identity.display();
            }
        }
    }
}

Matrix getInverse(Matrix m)
{
    if (!m.isOkay())
    {
        cout << endl;
        cout << "Hence, we cannot invert it";
    }
    else if (!m.isSquare())
    {
        cout << endl;
        cout << "Only square matrices can be inverted";
    }
    else
    {
        int rows = m.getRows();
        int cols = m.getCols();

        Matrix clone_m;
        Matrix inverse(rows, "identity");
        clone_m.clone(m);
        float **data = clone_m.getData();

        bool row_to_exchange;

        for (int row = 0; row < rows; row++)
        {
            if (data[row][row] == 0)
            {
                for (int new_row = row + 1; new_row < rows; new_row++)
                {
                    if (data[new_row][row] != 0)
                    {
                        clone_m.rowExchange(new_row, row);
                        inverse.rowExchange(new_row, row);
                        row_to_exchange = false;
                        break;
                    }
                }
                if (row_to_exchange) // inversion failed
                {
                    cout << endl;
                    cout << "This matrix is not invertible";
                    return Matrix(false);
                }
            }

            for (int i = 0; i < rows; i++)
            {
                if (i != row)
                {
                    inverse.rowAdd(i, row, data[row][row], -data[i][row]);
                    clone_m.rowAdd(i, row, data[row][row], -data[i][row]);
                }
            }
        }

        if (!isDiagonal(clone_m))
        {
            cout << endl;
            cout << "This matrix is not invertible";
            return Matrix(false);
        }

        for (int i = 0; i < rows; i++)
        {
            if (data[i][i] == 0.0)
            {
                cout << endl;
                cout << "This matrix is not invertible";
                return Matrix(false);
            }
            else if (data[i][i] != 1.0)
            {
                inverse.rowMultiply(i, (1.0 / data[i][i]));
                clone_m.rowMultiply(i, (1.0 / data[i][i]));
            }
        }
        return inverse;
    }
    return Matrix(false);
}

float diagonalProduct(Matrix m)
{
    if (!m.isOkay())
    {
        cout << endl;
        cout << "Hence, we cannot obtain its diagonal product";
        return 0.0;
    }
    else if (!m.isSquare())
    {
        cout << endl;
        cout << "Diagonal is not defined for a rectangular matrix";
        return 0.0;
    }
    return 0.0;
}

float det(Matrix m)
{
    if (!m.isOkay())
    {
        cout << endl;
        cout << "Hence, we cannot obtain its determinant";
        return 0.0;
    }
    else if (!m.isSquare())
    {
        cout << endl;
        cout << "Determinant is not defined for a rectangular matrix";
        return 0.0;
    }
    else
    {
        if (isZero(m))
            return 0.0;
        else if (isUpperTriangular(m) || isLowerTriangular)
            return diagonalProduct(m);
    }
    return 0.0;
}
#endif