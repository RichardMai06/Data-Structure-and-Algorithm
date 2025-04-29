#include <iostream>
using namespace std;

int fibonacci(int n);

int main()
{
	int num;
	do
	{
		cout << "Enter index in the fibonacci sequence: ";
		cin >> num;
	} while (num < 0);
	cout << fibonacci(num) << endl;
}

int fibonacci(int n)
{
	if (n == 0 || n == 1)
	{
		return n;
	}
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}
