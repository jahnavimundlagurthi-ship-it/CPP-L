
#include <iostream>
using namespace std;

// Call by reference
void swapRef(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Call by pointer
void swapPtr(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int x = 10, y = 20;

    swapRef(x, y);

    cout << "After swapRef: x = " << x << " y = " << y << endl;

    swapPtr(&x, &y);

    cout << "After swapPtr: x = " << x << " y = " << y << endl;

    // Alias (reference variable)
    int &alias = x;
    alias = 99;

    cout << "x via alias = " << x << endl;

    return 0;
}