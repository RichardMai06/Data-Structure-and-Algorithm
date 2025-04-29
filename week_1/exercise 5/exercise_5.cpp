#include <iostream>
using namespace std;

bool isSorted (int a[], int n);

int main ()
{
    int a[] = {1, 2, 3, 4, 3}, n = sizeof(a) / sizeof (int);
    if (isSorted(a, n))
    {
        cout << "The array is sorted." << endl;
    }
    else
    {
        cout << "The array is not sorted." << endl;
    }
}

bool isSorted (int a[], int n)
{
    if (n == 1 || n == 0)
    {
        return true;
    }
    if (a[0] > a[1])
    {
        return false;
    }
    isSorted (a + 1, n - 1);
}
