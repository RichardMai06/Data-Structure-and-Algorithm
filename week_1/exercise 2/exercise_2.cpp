#include <iostream>
using namespace std;

int factorial(int n);

int main()
{
	int num;
	do
	{
		cout << "Enter number to calculate: ";
		cin >> num;
	} while (num < 0);
	cout << factorial(num) << endl;
	return 0;
}

int factorial(int n)
{
	int fact = 1;
	if (n == 0 || n == 1)
	{
		return n;
	}
	return fact * n * factorial(n - 1);
}
