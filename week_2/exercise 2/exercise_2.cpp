// Test case:
// Input: 
//  5
//  1 3 5 7 9 
//  5
// Output: 
//  2

#include <iostream>
using namespace std;

int linearSearchWithSetinel(int a[], int n, int k);

int main()
{
    int n, k;
    do
    {
        cout << "Enter size: ";
        cin >> n;
    } while (n <= 0);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter number: ";
        cin >> a[i];
    }
    cout << "Enter number to find: ";
    cin >> k;
    cout << "Number " << k << " is at index " << linearSearchWithSetinel(a, n, k) << endl;
    return 0;
}

int linearSearchWithSetinel(int a[], int n, int k)
{
    int last = a[n - 1], i = 0;
    a[n - 1] = k;
    while (a[i] != k)
    {
        i++;
    }
    a[n - 1] = last;
    if (i < n - 1 || a[n - 1] == k)
    {
        return i;
    }
    return -1;
}
