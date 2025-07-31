#include <iostream>
#include <vector>
using namespace std;

int LinearSum(const std::vector<int>& A, int n) {
    if (n == 1) {
        return A[0];
    } else {
        return LinearSum(A, n - 1) + A[n - 1];
    }
}

int Linearsum2(vector <int> A, int n, int sum)
{
    if (n == 0)
    {
        return sum;
    }

    //return Linearsum2(A, n-1, sum) + Linearsum2(A, n , sum);
    return Linearsum2(A, n-1, sum + A[n-1]);
}
int main(){
    std::vector<int> A = {1, 2, 3, 4, 5};
    std::cout << LinearSum(A, 5) << std::endl;
    return 0;
}