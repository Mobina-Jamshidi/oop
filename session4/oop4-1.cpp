#include <iostream>
using namespace std;

// Base class: Car
class Car {
public:
    // Virtual method: all cars can start, but behavior might differ
    virtual void Start() {
        cout << "Car is starting..." << endl;
    }

    // Common method for all cars
    void ShowInfo() {
        cout << "This is a general car." << endl;
    }
};

// Derived class: Pride inherits from Car
class Pride : public Car {
public:
    // Override Start method with specific behavior for Pride
    void Start() override {
        cout << "Pride starts with vibration!" << endl;
    }

    // Feature specific to Pride
    void CheapFeature() {
        cout << "Pride has low fuel consumption." << endl;
    }
};

// Derived class: Benz inherits from Car
class Benz : public Car {
public:
    // Override Start method with specific behavior for Benz
    void Start() override {
        cout << "Benz starts silently and luxuriously!" << endl;
    }

    // Feature specific to Benz
    void LuxuryFeature() {
        cout << "Benz has massage seats." << endl;
    }
};

// Main function to test the classes
int main() {
    // Create a Pride object
    Pride p;
    cout << "--- Pride ---" << endl;
    p.Start();            // Overridden Start() from Pride
    p.ShowInfo();         // Common method from Car
    p.CheapFeature();     // Pride-specific method

    cout << "\n--- Benz ---" << endl;

    // Create a Benz object
    Benz b;
    b.Start();            // Overridden Start() from Benz
    b.ShowInfo();         // Common method from Car
    b.LuxuryFeature();    // Benz-specific method

    cout << "\n--- Polymorphism in action ---" << endl;

    // Using base class pointers to demonstrate polymorphism
    Car* car1 = &p;
    Car* car2 = &b;

    car1->Start();  // Executes Pride's Start() due to polymorphism
    car2->Start();  // Executes Benz's Start() due to polymorphism

    return 0;
}
