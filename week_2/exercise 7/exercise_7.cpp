// Test case:
// Input :
//  6
//  -1 0 1 2 -1 -4
// Output: 
//  [-1, -1, 2]
//  [-1, 0, 1]

#include <iostream>
using namespace std;

void selectionSort (int a[], int n);
void findTriplet (int a[], int n);

int main()
{
    int n;
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
    findTriplet(a, n);
    return 0;
}

void selectionSort (int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i; j < n; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

void findTriplet (int a[], int n)
{
    selectionSort(a, n);
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && a[i] == a[i-1])
        {
            continue;
        }
        int left = i + 1, right = n - 1;
        while (left < right)
        {
            int sum = a[i] + a[left] + a[right];
            if (sum == 0)
            {
                cout << "[" << a[i] << ", " << a[left] << ", " << a[right] << "]" << endl;
                left++;
                right--;
                while (a[left] == a[left + 1])
                {
                    left++;
                }
                while (a[right] == a[right - 1])
                {
                    right--;
                }
            }
            else if (sum < 0)
            {
                left++;
            }
            else 
            {
                right--;
            }
        }
    }
}
