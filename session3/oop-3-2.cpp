
#include <iostream>
using namespace std;

// Function Template with multiple types
template <typename T, typename U>
auto Add(T a, U b) -> decltype(a + b) {
    return a + b;
}

// Overloaded version for int
int Add(int a, int b) {
    return a + b;
}

// Overloaded version for double
double Add(double a, double b) {
    return a + b;
}

int main() {
    auto result1 = Add(3, 4);            // Calls int version
    auto result2 = Add(2.5, 3.5);        // Calls double version
    auto result3 = Add(5, 2.7);          // Calls template with int + double
    auto result4 = Add(10.5, 2);         // Calls template with double + int

    cout << "Result 1 (int + int): " << result1 << endl;
    cout << "Result 2 (double + double): " << result2 << endl;
    cout << "Result 3 (int + double): " << result3 << endl;
    cout << "Result 4 (double + int): " << result4 << endl;

    return 0;
}
