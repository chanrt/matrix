#ifndef MATRIX
#define MATRIX

#define ELEMENT data[row][col]

#include <iostream>
#include <string>

using namespace std;

float **getNewArray(int m, int n)
{
    float **array = new float *[m];
    for (int i = 0; i < m; i++)
        array[i] = new float[n];

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            array[i][j] = 0.0;
    }

    return array;
}

void copyArray(float **source, float **target, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            target[i][j] = source[i][j];
    }
}

class Matrix
{
private:
    // entries
    float **data;
    // dimensions
    int rows, cols;
    // data array isAlloc, isInit
    bool isAlloc, isInit;
    // output validity parameter
    bool isValid;

    bool allInts()
    {
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                if (ELEMENT - int(ELEMENT) != 0.0)
                    return false;
            }
        }
        return true;
    }

    int getPrec(float f)
    {
        int prec = 0;

        while(f - int(f) != 0.0)
        {
            if(prec < -5)
                break;

            f = 10.0 * f;
            prec--;
        }
        return prec;
    }

    int getMatrixPrec()
    {
        int minimum = 0;
        int prec;

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                if((prec = getPrec(ELEMENT)) < minimum)
                    minimum = prec;
            }
        }
        return minimum;
    }

public:
    // <--- constructors --->

    // default
    Matrix()
    {
        isAlloc = false;
        isInit = false;
    }

    // flag matrices
    Matrix(bool validity)
    {
        isValid = validity;
    }

    // square matrix, not initialized
    Matrix(int n)
    {
        data = getNewArray(n, n);
        rows = cols = n;

        isAlloc = true;
        isInit = false;
        isValid = false;
    }

    // sqaure matrix, initialized
    Matrix(float **array, int n)
    {
        data = getNewArray(n, n);
        rows = cols = n;

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
                ELEMENT = array[row][col];
        }

        isAlloc = true;
        isInit = true;
        isValid = true;
    }

    // rectangluar matrix, not initialized
    Matrix(int m, int n)
    {
        data = getNewArray(m, n);
        rows = m;
        cols = n;

        isAlloc = true;
        isInit = false;
        isValid = true;
    }

    // rectangular matrix, initialized
    Matrix(float **array, int m, int n)
    {
        data = getNewArray(m, n);
        rows = m;
        cols = n;

        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
                ELEMENT = array[row][col];
        }

        isAlloc = true;
        isInit = true;
        isValid = true;
    }

    // custom matrices
    Matrix(int n, const string s)
    {
        data = getNewArray(n, n);
        rows = cols = n;

        if (s == "identity")
        {
            for (int i = 0; i < rows; i++)
                data[i][i] = 1.0;

            isAlloc = true;
            isInit = true;
            isValid = true;
        }
    }

    // using another matrix
    void clone(Matrix m)
    {
        if (!m.isOkay())
        {
            cout << endl;
            cout << "You cannot use such a matrix for cloning";

            isAlloc = isInit = isValid = false;
        }
        else if (!m.getValid())
        {
            cout << endl;
            cout << "You cannot use an invalid matrix for cloning";

            isAlloc = isInit = isValid = false;
        }
        else
        {
            rows = m.getRows();
            cols = m.getCols();
            data = getNewArray(rows, cols);
            copyArray(m.getData(), data, rows, cols);

            isAlloc = true;
            isInit = true;
            isValid = true;
        }
    }

    // <--- Constructors end --->

    // <--- Entering data --->
    void input()
    {
        if (!isAlloc)
        {
            cout << endl;
            cout << "Matrix has not been allocated yet, you cannot initialize it";
        }
        else if (isInit)
        {
            cout << endl;
            cout << "Matrix has already been initialized, you cannot overwrite it";
        }
        else
        {
            cout << endl;
            cout << "Enter " << rows << " rows and " << cols << " columns:";
            cout << endl;

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                    cin >> ELEMENT;
            }

            isInit = true;
            isValid = true;
        }
    }

    // <--- Displaying matrix --->
    void display()
    {
        if (!isValid)
        {
            cout << endl;
            cout << "This matrix is a result of an undefined operation and cannot be displayed";
        }
        else if (!isOkay())
        {
            cout << endl;
            cout << "Hence, the matrix cannot be displayed";
        }
        else // matrix can be displayed
        {
            cout << endl;
            if (allInts())
            {
                for (int row = 0; row < rows; row++)
                {
                    cout << endl;
                    for (int col = 0; col < cols; col++)
                        printf("%.0f\t", ELEMENT);
                }
            }
            else
            {
                int prec = getMatrixPrec();
                for (int row = 0; row < rows; row++)
                {
                    cout << endl;
                    for (int col = 0; col < cols; col++)
                    {
                        switch(prec)
                        {
                            case -1:
                                printf("%.1f\t", ELEMENT);
                                break;
                            case -2:
                                printf("%.2f\t", ELEMENT);
                                break;
                            case -3:
                                printf("%.3f\t", ELEMENT);
                                break;
                            case -4:
                                printf("%.4f\t", ELEMENT);
                                break;
                            case -5:
                                printf("%.5f\t", ELEMENT);
                                break;
                            case -6:
                            default:
                                printf("%.6f\t", ELEMENT);
                                break;
                        }
                    }
                }
            }
        }
    }

    // <--- Basic operations --->

    // assignment
    Matrix operator=(Matrix m)
    {
        if (!isOkay() || !m.isOkay())
        {
            cout << endl;
            cout << "As a result, it cannot be assigned to an other matrix";
            return Matrix(false);
        }
        return Matrix(false);
    }

    // addition
    Matrix operator+(Matrix m)
    {
        if (!isOkay() || !m.isOkay())
        {
            cout << endl;
            cout << "As a result, the matrices cannot be added";
            return Matrix(false);
        }
        else if (!sameDim(*this, m))
        {
            cout << endl;
            cout << "Both the matrices need to have the same dimension in order to perform addition";
            return Matrix(false);
        }
        else
        {
            float **addend = m.getData();
            float **sum = getNewArray(rows, cols);

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                    sum[row][col] = ELEMENT + addend[row][col];
            }
            return Matrix(sum, rows, cols);
        }
    }

    // negation
    Matrix operator-()
    {
        if (!isOkay())
        {
            cout << endl;
            cout << "As a result, the matrix cannot be negated";
            return Matrix(false);
        }
        else
        {
            float **negative = getNewArray(rows, cols);

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                    negative[row][col] = -ELEMENT;
            }
            return Matrix(negative, rows, cols);
        }
    }

    // subtraction
    Matrix operator-(Matrix m)
    {
        if (!isOkay() || !m.isOkay())
        {
            cout << endl;
            cout << "As a result, scalar multiplication cannot be done";
            return Matrix(false);
        }
        else if (!sameDim(*this, m))
        {
            cout << endl;
            cout << "Both the matrices need to have the same dimension in order to perform subtraction";
            return Matrix(false);
        }
        else
        {
            float **subtrahend = m.getData();
            float **diff = getNewArray(rows, cols);

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                    diff[row][col] = ELEMENT - subtrahend[row][col];
            }
            return Matrix(diff, rows, cols);
        }
    }

    // scalar multiplication
    Matrix operator*(float f)
    {
        if (!isOkay())
        {
            cout << endl;
            cout << "As a result, scalar multiplication cannot be done";
            return Matrix(false);
        }
        else
        {
            float **product = getNewArray(rows, cols);

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                    product[row][col] = f * ELEMENT;
            }
            return Matrix(product, rows, cols);
        }
    }

    // matrix multiplication
    Matrix operator*(Matrix m)
    {
        if (!isOkay() || !m.isOkay())
        {
            cout << endl;
            cout << "As a result, matrix multiplcation cannot be done";
            return Matrix(false);
        }
        else if (cols != m.getRows())
        {
            cout << endl;
            cout << "Both the matrices need to have the same dimension in order to perform subtraction";
            return Matrix(false);
        }
        else
        {
            float **multiplier = m.getData();

            int num_rows = rows;
            int num_cols = m.getCols();
            int iterator_limit = cols;
            float **product = getNewArray(num_rows, num_cols);

            for (int row = 0; row < num_rows; row++)
            {
                for (int col = 0; col < num_cols; col++)
                {
                    float sum = 0.0;
                    for (int i = 0; i < iterator_limit; i++)
                        sum += data[row][i] * multiplier[i][col];
                    product[row][col] = sum;
                }
            }
            return Matrix(product, num_rows, num_cols);
        }
    }

    // <--- Basic operations end --->

    // Check before addition
    bool sameDim(Matrix m1, Matrix m2)
    {
        return (m1.getRows() == m2.getRows() && m1.getCols() == m2.getCols());
    }

    // Check before some operations
    bool isOkay()
    {
        if (!isAlloc)
        {
            cout << endl;
            cout << "Matrix not allocated";
            return false;
        }
        else if (!isInit)
        {
            cout << endl;
            cout << "Matrix not initialized";
            return false;
        }
        else
            return true;
    }

    // <--- Elementary operations --->
    void rowExchange(int r1, int r2)
    {
        if (!isOkay())
        {
            cout << endl;
            cout << "Hence, its rows cannot be exchanged";
        }
        else if (r1 >= rows)
        {
            cout << endl;
            cout << "Matrix does not have row #" << r1;
        }
        else if (r2 >= rows)
        {
            cout << endl;
            cout << "Matrix does not have row #" << r2;
        }
        else
        {
            float *temp = new float[cols];

            for (int col = 0; col < cols; col++)
            {
                temp[col] = data[r1][col];
                data[r1][col] = data[r2][col];
                data[r2][col] = temp[col];
            }
            delete (temp);
        }
    }

    void rowMultiply(int r, float f)
    {
        if (!isOkay())
        {
            cout << endl;
            cout << "Hence, its rows cannot be exchanged";
        }
        else if (r >= rows)
        {
            cout << endl;
            cout << "Matrix does not have row #" << r;
        }
        else
        {
            for (int col = 0; col < cols; col++)
                data[r][col] = f * data[r][col];
        }
    }

    void rowAdd(int target, int source, float target_multiplier, float source_multiplier)
    {
        if (!isOkay())
        {
            cout << endl;
            cout << "Hence, its rows cannot be exchanged";
        }
        else if (target >= rows)
        {
            cout << endl;
            cout << "Matrix does not have row #" << target;
        }
        else if (source >= rows)
        {
            cout << endl;
            cout << "Matrix does not have row #" << source;
        }
        else
        {
            for (int col = 0; col < cols; col++)
                data[target][col] = (target_multiplier * data[target][col]) + (source_multiplier * data[source][col]);
        }
    }

    // <--- setters --->
    void setInit(bool value)
    {
        isInit = value;
    }

    void setValid(bool value)
    {
        isValid = value;
    }

    void setElement(int i, int j, float k)
    {
        data[i][j] = k;
    }

    // <--- getters --->

    bool getAlloc()
    {
        return isAlloc;
    }

    bool getInit()
    {
        return isInit;
    }

    bool getValid()
    {
        return isValid;
    }

    bool isSquare()
    {
        return (rows == cols);
    }

    int getRows()
    {
        return rows;
    }

    int getCols()
    {
        return cols;
    }

    float **getData()
    {
        return data;
    }
};

#include "properties.cpp"
#include "operations.cpp"
#include "solver.cpp"

#endif
