#include <iostream>
class Circle {
private:
    double radius;

public:
    // 构造函数
    Circle(double r) : radius(r) {
        std::cout << "Constructor called, radius = " << radius << std::endl;
    }

    // 析构函数
    // ~Circle() {
    //     std::cout << "Destructor called, cleaning up radius = " << radius << std::endl;
    //}
};

int main() {
    Circle c1(5.0); // 创建对象 c1，调用构造函数
    Circle c2(10.0); // 创建对象 c2，调用构造函数

    // c1 和 c2 在 main 函数结束时被销毁，调用析构函数
    return 0;
}