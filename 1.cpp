#include <iostream>

int main() {
    // Step 1: Declare an integer and initialize it
    int value = 21;

    // Step 2: Declare A as a pointer to integer and point it to 'value'
    int* A = &value;

    // Step 3: Use a reference to A's referent (the value that A points to)
    int& ref = *A;

    // Step 4: Write an expression whose value is twice the value of A's referent
    int result = 2 * ref;

    // Print the results
    std::cout << "Original value: " << *A << std::endl; // Output: 21
    std::cout << "Twice the value of A's referent: " << result << std::endl;

    return 0;
}
