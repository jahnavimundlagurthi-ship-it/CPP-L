#include <iostream>
using namespace std;

class Point {
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point add(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }

    Point &setX(int v) { this->x = v; return *this; }
    Point &setY(int v) { this->y = v; return *this; }

    void show() const { cout << "(" << x << "," << y << ")\n"; }
};

void shift(Point &p) { p.setX(99); }
void tryshift(Point p) { p.setX(-1); }

int main() {
    Point a(1, 2), b(3, 4);
    Point c = a.add(b);
    c.show();
    shift(a);
    a.show();
    tryshift(b);
    b.show();
    return 0;
}