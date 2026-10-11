#include <iostream>
using namespace std;

class Widget {
    int id;

public:
    static int count;

    Widget() {
        id = ++count;
        cout << "Created w" << id << endl;
    }

    ~Widget() {
        --count;
        cout << "Destroyed w" << id << endl;
    }

    static int alive() { return count; }
};

int Widget::count = 0;

int main() {
    Widget a, b;
    cout << "Alive = " << Widget::alive() << endl;
    {
        Widget c;
        cout << "Alive = " << Widget::alive() << endl;
    }
    cout << "Alive = " << Widget::alive() << endl;
    return 0;
}