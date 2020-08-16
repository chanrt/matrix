#ifndef ELEMENT
#define ELEMENT data[row][col]
#endif

#ifndef ELEMENT_TRANSPOSE
#define ELEMENT_TRANSPOSE data[col][row]
#endif

#ifndef PROPERTIES
#define PROPERTIES

#include "matrix.cpp"

bool isZero(Matrix m)
{
    if(!m.isOkay())
    {
        cout << endl;
        cout << "Hence, the required property cannot be determined";
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();
        int cols = m.getCols();

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                if(ELEMENT != 0.0)
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool isDiagonal(Matrix m)
{
    if(!m.isOkay())
    {
        cout << endl;
        cout << "Hence, the required property cannot be determined";
    }
    else if(!m.isSquare())
    {
        cout << endl;
        cout << "A diagonal is not defined for rectangular matrices";
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();
        int cols = m.getCols();

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                if(row != col && ELEMENT != 0.0)
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool isScalar(Matrix m)
{
    if(isDiagonal(m))
    {
        float **data = m.getData();
        int rows = m.getRows();
        float top_left = data[0][0];

        if(top_left == 0.0)
            return false;
        
        for(int i = 1; i < rows; i++)
        {
            if(data[i][i] != top_left)
                return false;
        }
        return true;
    }
    return false;
}

bool isUnitary(Matrix m)
{
    if(isDiagonal(m))
    {
        float **data = m.getData();
        if(data[0][0] == 1.0)
            return true;
        else 
            return false;
    }
    return false;
}

bool isUpperTriangular(Matrix m)
{
    if(!m.isOkay())
    {
        cout << endl;
        cout << "Hence, the required property cannot be determined";
    }
    else if(!m.isSquare())
    {
        cout << endl;
        cout << "Triangularity is not defined for rectangular matrices";
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();
        int cols = m.getCols();

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                if(row > col && ELEMENT != 0.0)
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool isLowerTriangular(Matrix m)
{
    if(!m.isOkay())
    {
        cout << endl;
        cout << "Hence, the required property cannot be determined";
    }
    else if(!m.isSquare())
    {
        cout << endl;
        cout << "Triangularity is not defined for rectangular matrices";
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();
        int cols = m.getCols();

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < cols; col++)
            {
                if(row < col && ELEMENT != 0.0)
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool isSymmetric(Matrix m)
{
    if(!m.isOkay())
    {
        cout << endl;
        cout << "Hence, the required property cannot be determined";
    }
    else if(!m.isSquare())
    {
        cout << endl;
        cout << "Symmetry is not defined for rectangular matrices";
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < row; col++)
            {
                if(ELEMENT != ELEMENT_TRANSPOSE)
                    return false;
            }
        }
        return true;
    }
    return false;
}

bool isSkewSymmetric(Matrix m)
{
    if(!m.isOkay())
    {
        cout << endl;
        cout << "Hence, the required property cannot be determined";
    }
    else if(!m.isSquare())
    {
        cout << endl;
        cout << "Skew symmetry is not defined for rectangular matrices";
    }
    else
    {
        float **data = m.getData();
        int rows = m.getRows();

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col < row; col++)
            {
                if(ELEMENT != -ELEMENT_TRANSPOSE)
                    return false;
            }
        }

        for(int i = 0; i < rows; i++)
        {
            if(data[i][i] != 0.0)
                return false;
        }
        return true;
    }
    return false;
}
#endif