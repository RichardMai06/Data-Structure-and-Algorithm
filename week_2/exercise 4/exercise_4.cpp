// Test case:
// Input :
//  10 
//  1 2 3 4 5 6 7 8 9 10
//  5
// Output: 
//  15

#include <iostream>
using namespace std;

bool canShip(int a[], int n, int days, int capacity);
int minCapacity (int a[], int n, int days);

int main()
{
    int n, days;
    do
    {
        cout << "Numbers of package on the conveyor belt: ";
        cin >> n;
    } while (n <= 0);
    int weight[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter package's weight: ";
        cin >> weight[i];
    }
    do 
    {
        cout << "Enter maximum day of shipping: ";
        cin >> days;
    } while (days <= 0);
    cout << "The minimum capacity to ship is: " << minCapacity(weight, n, days) << endl;
    return 0;
}

bool canShip(int a[], int n, int days, int capacity)
{
    int current_weight = 0, days_needed = 1;
    for (int i = 0; i < n; i++)
    {
        if (current_weight + a[i] > capacity)
        {
            days_needed++;
            current_weight = 0;
        }
        current_weight += a[i];
    }
    return days_needed <= days;
}

int minCapacity (int a[], int n, int days)
{
    int left = a[0], right = 0, result = 0;
    for (int i = 0; i < n; i++)
    {
        if (left < a[i])
        {
            left = a[i];
        }
        right += a[i];
    }

    while (left <= right)
    {
        int mid = (right + left)/2;
        if (canShip(a, n, days, mid))
        {
            result = mid;
            right = mid - 1;
        }
        else 
        {
            left = mid + 1;
        }
    }
    return result;
}
