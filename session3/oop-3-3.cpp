
#include <iostream>
using namespace std;

// Template base class
template <typename T>
class Parent {
protected:
    virtual T Add(T a, T b) {
        return a + b;
    }
};

// Derived class inheriting from Parent<int>
class Child : public Parent<int> {
public:
    int Add(int a, int b) override {
        int c = Parent<int>::Add(5, 10);  // Calls base class method
        return c + 20;
    }
};

int main() {
    Child obj;
    int result = obj.Add(1, 2);  // input values are ignored in this version
    cout << "Result: " << result << endl;  // Output: 35
    return 0;
}
