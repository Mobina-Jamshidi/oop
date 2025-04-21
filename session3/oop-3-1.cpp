
#include <iostream>
using namespace std;

// Function Overloading Examples

int Add(int a, int b) {
    return a + b;
}

int Add(int a, int b, int c) {
    return a + b + c;
}

int Add(int a, int k, int w) {
    return a + k + w;
}

double Add(double a, double b) {
    return a + b;
}

int main() {
    int a1 = Add(4, 6);               // calls Add(int, int)
    int a2 = Add(3, 4, 5);            // calls Add(int, int, int)
    double a3 = Add(2.5, 3.5);        // calls Add(double, double)

    cout << "a1 = " << a1 << endl;
    cout << "a2 = " << a2 << endl;
    cout << "a3 = " << a3 << endl;

    return 0;
}
