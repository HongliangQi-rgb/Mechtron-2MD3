#include <iostream>
#include <string>

template <typename V1, typename V2> // template for two different types
class Pair {
    private:
        V1 value1;  
        V2 value2; 

    public:
        Pair(V1 value1 , V2 value2) : value1(value1), value2(value2) {} // constructor for value1 and value2

        void print() const {
            std::cout << "<" << value1 << ", " << value2 << ">" << std::endl;
        }
};

int main() {
    Pair<int, double> p1(1, 7.3);
    p1.print();

    Pair<std::string, double> p2("hello", 7.7);
    p2.print();

    Pair<float, long> p3(1.2, 777777773);
    p3.print();

    return 0;
}
