#include <iostream>
#include <cstring>
using namespace std;

class Text {
    char *buf;
public:
    Text(const char *s = "") {
        buf = new char[strlen(s)+1];
        strcpy(buf, s);
    }
    
    // Copy Constructor (Deep Copy)
    Text(const Text &o) {
        buf = new char[strlen(o.buf)+1];
        strcpy(buf, o.buf);
    }
    
    // Assignment Operator (Deep Copy)
    Text& operator=(const Text &o) {
        // guard against self-assignment
        if (this != &o) { 
            delete[] buf; // free old memory
            buf = new char[strlen(o.buf)+1];
            strcpy(buf, o.buf);
        }
        return *this; // enables chained assignment (a = b = c)
    }
    
    // Destructor
    ~Text() {
        delete[] buf;
    }
    
    void show() const {
        cout << buf << endl;
    }
};

int main() {
    Text a("alpha"), b("beta");
    b = a; // operator= runs -> deep copy
    a.show(); // Outputs: alpha
    b.show(); // Outputs: alpha
    return 0;
}