#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str);

int main() 
{
    int n = 3;  // Example length
    generateBinaryStrings(n, "");
    return 0;
}

void generateBinaryStrings(int n, string str) 
{
    if (str.length() == n) 
    {
        cout << str << endl;
        return;
    }
    generateBinaryStrings(n, str + "0");
    generateBinaryStrings(n, str + "1");
}
