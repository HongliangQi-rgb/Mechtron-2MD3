#include <cstdlib>
#include <iostream>
#include <string>

int main()
{
    std::string author = "1";
    //std::string& writor = author;
    author = "3";
    //writor = "3";
    std::cout << author << std::endl;
    //std::cout << writor << std::endl;
    return 0;
}