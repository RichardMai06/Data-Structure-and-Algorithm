// Test case:
// Input :
//  6
//  2 3 1 2 4 3
//  7 
// Output: 
//  2

#include <iostream>
using namespace std;

int minLength (int a[], int n, int target);

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
    cout << "The shortest subarray has the sum greater or equal than target has " << minLength(a, n, target) << " element." << endl;
    return 0;
}

int minLength (int a[], int n, int target)
{
    int min_length = n - 1, left = 0, right = 0, sum = 0;
    for (;right < n; right++)
    {
        sum += a[right];
        while (sum >= target)
        {
            int length = right - left + 1;
            if (length < min_length)
            {
                min_length = length;
            }
            sum -= a[left];
            left++;
        }
    }
    return min_length;
}
