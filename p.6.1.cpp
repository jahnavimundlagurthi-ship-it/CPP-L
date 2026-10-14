#include <iostream> 
using namespace std; 

class Complex { 
    double re, im; 
public: 
    Complex(double r = 0, double i = 0) : re(r), im(i) {} 

    // Overloading '+' operator as a member function
    Complex operator+(const Complex &o) const { 
        return Complex(re + o.re, im + o.im); 
    } 

    // Overloading '==' operator as a member function
    bool operator==(const Complex &o) const { 
        return re == o.re && im == o.im; 
    } 

    // Overloading '<<' operator as a friend function for printing
    friend ostream& operator<<(ostream &os, const Complex &c) { 
        os << c.re << (c.im >= 0 ? "+" : "") << c.im << "i"; 
        return os; // enables chaining (e.g., cout << a << b;)
    } 
}; 

int main() { 
    Complex a(2, 3), b(1, -4); 
    
    cout << "a = " << a << ", b = " << b << endl; 
    cout << "a + b = " << (a + b) << endl; 
    cout << "a == b ? " << (a == b ? "yes" : "no") << endl; 

    return 0; 
}