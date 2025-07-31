#include <iostream>
using namespace std;

class Person {
public:
    string name;
    int age;

    // 使用初始化列表
    Person(string n, int a) : name(n), age(a) {}

    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    Person p("Charlie", 35);
    p.display(); // 输出：Name: Charlie, Age: 35
    return 0;
}
