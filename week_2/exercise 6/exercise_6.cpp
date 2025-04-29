// Test case:
// Input :
//  5
//  1 2 3 4 6
//  5
// Output: 
//  YES

#include <iostream>
using namespace std;

bool sumTarget (int a[], int n, int k);

int main()
{
    int n, target;
    do
    {
        cout << "Enter number of elements: ";
        cin >> n;
    } while (n <= 0);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter element: ";
        cin >> a[i];
    }
    do 
    {
        cout << "Enter target: ";
        cin >> target;
    } while (target <= 0);
    if (sumTarget(a, n, target))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}

bool sumTarget (int a[], int n, int k)
{
    int left = 0, right = n - 1;
    while (left < right)
    {
        int sum = a[left] + a[right];
        if (sum == k)
        {
            return true;
        }
        else if (sum < k)
        {
            left++;
        }
        else 
        {
            right--;
        }
    }
    return false;
}
