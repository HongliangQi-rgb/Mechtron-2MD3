#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
    const int n = 7;
    const int m = 24*n;
    int counter[m];
    std::cout <<sizeof(counter[m])  << std::endl;
}