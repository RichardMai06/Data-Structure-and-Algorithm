#include "algorithm.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    string algorithm, input_path, output_path, temp;
    int n, *a;
    for (int i = 1; i < argc; i++)
    {
        temp = argv[i];
        if (temp == "-a" && i + 1 < argc)
        {
            algorithm = argv[++i];
        }
        else if (temp == "-i" && i + 1 < argc)
        {
            input_path = argv[++i];
        }
        else if (temp == "-o" && i + 1 < argc)
        {
            output_path = argv[++i];
        }
    }
    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        cerr << "Can't open file." << endl;
    }
    else
    {
        fin >> n;
        a = new int[n];
        for (int i = 0; i < n; i++)
        {
            fin >> a[i];
        }
    }
    fin.close();
    if (algorithm == "selection-sort")
    {
        selectionSort(a, n);
    }
    else if (algorithm == "insertion-sort")
    {
        insertionSort(a, n);
    }
    else if (algorithm == "bubble-sort")
    {
        bubbleSort(a, n);
    }
    else if (algorithm == "shaker-sort")
    {
        shakerSort(a, n);
    }
    else if (algorithm == "shell-sort")
    {
        shellSort(a, n);
    }
    else if (algorithm == "heap-sort")
    {
        heapSort(a, n);
    }
    else if (algorithm == "merge-sort")
    {
        mergeSort(a, 0, n - 1);
    }
    else if (algorithm == "quick-sort")
    {
        quickSort(a, 0, n - 1);
    }
    else if (algorithm == "counting-sort")
    {
        countingSort(a, n);
    }
    else if (algorithm == "radix-sort")
    {
        radixSort(a, n);
    }
    else if (algorithm == "flash-sort")
    {
        flashSort(a, n);
    }
    ofstream fout("output.txt");
    if (!fout.is_open())
    {
        cerr << "Can't open file." << endl;
    }
    else
    {
        fout << n << endl;
        for (int i = 0; i < n; i++)
        {
            fout << a[i] << " ";
            if (i == n - 1)
            {
                fout << endl;
            }
        }
    }
    delete[] a;
    return 0;
}
