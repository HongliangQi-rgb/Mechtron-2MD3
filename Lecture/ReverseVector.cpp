#include <iostream>
#include <vector>
using namespace std;

void ReverseVector(vector<int> &A , int i , int j)
{
    // if (i >= j)
    // {
    //     cout << A[i] << endl;
    // }
    // return ReverseVector( A , i+1 , j-1 );
    if (i<j)
    {
        swap(A[i], A[j]);
        ReverseVector (A ,  i+1, j-1);
    }
}