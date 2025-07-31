#include <iostream>
#include <cmath>
using namespace std;

class Progression {
  public:
    Progression(long f = 0) : first(f), cur(f) {} // constructor the first and current value
    virtual ~Progression() {} // destructor
    void printProgression(int n); 
  protected:
    virtual long firstValue() = 0; // both of them are pure virtual function
    virtual long nextValue() = 0; //rewrite in the derived class
  protected:
    long first;  // intialize first and current value
    long cur;    
};

void Progression::printProgression(int n) {
    cout << firstValue();          
    for (int i = 2; i <= n; i++) {  // print 9 next value after first value
        cout << ' ' << nextValue();
    }
    cout << endl;
}

class AbsoluteProgression : public Progression { //polymorphism
  public:
    AbsoluteProgression(long f = 200, long s = 198); // default constructor with 200 and 198, can also be custom constructor
  protected:
    virtual long firstValue(); 
    virtual long nextValue();
  private:
    long second;    // second value
    long prev;      // previous value
    bool secondValue; // a boolean to check if the second value is printed
};

AbsoluteProgression::AbsoluteProgression(long f, long s): Progression(f), second(s), prev(0), secondValue(false) {} 
// constructor for the AbsoluteProgression class with the first value, second value, previous value and a boolean value secondValue
// set the secondValue to false first to make sure the second value can be printed after the first value
long AbsoluteProgression::firstValue() {
    cur = first;             
    secondValue = true;  //set second value to true to print the second value
    return cur;
}

long AbsoluteProgression::nextValue() {
    if (secondValue) {
        secondValue = false; // continue to print the next value after the second value
        prev = cur;      
        cur = second;    //prev is before cur
        return cur;
    } else {
        long temp = cur;             
        cur = std::abs(cur - prev);  
        prev = temp;                 // prev move backforward one step
        return cur;
    }
}

int main() {
    cout << "Absolute progression with default constructor:\n";
    AbsoluteProgression defaultProg;
    defaultProg.printProgression(10);

    cout << "Absolute progression with custom constructor:\n";
    AbsoluteProgression customProg(300, 297);
    customProg.printProgression(10);

    return 0;
}
