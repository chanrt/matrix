#include <iostream>
#include "matrix.cpp"

using namespace std;

int main()
{
    Matrix m(3,3);
    Matrix v(3,1);
    m.input();
    v.input();
    solveHeterogeneous(m,v).display();

    while(1);
}