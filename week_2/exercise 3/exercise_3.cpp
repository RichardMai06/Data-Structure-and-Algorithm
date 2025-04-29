// Test case:
// Input: 
//  5
//  3 4 5 1 2 
// Output: 
//  1

#include <iostream>
using namespace std;

int findMin(int a[], int n, int left, int right);

int main()
{
    int n, left, right;
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
    cout << "Smallest number in the array is " << findMin(a, n, left, right) << endl;
    return 0;
}

int findMin(int a[], int n, int left, int right)
{
    left = 0, right = n - 1;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (a[mid] > a[right])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return a[left];
}
