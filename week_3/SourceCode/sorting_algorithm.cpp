#include "algorithm.hpp"
#include <iostream>
using namespace std;

void swap(int &x, int &y)
{
    int temp = x;
    x = y; 
    y = temp;
}

int layer(int a, int max, int min, int m)
{
    return (int)(1.0 * (m - 1) * (a - min) / (max - min));
}

int partition (int a[], int left, int right)
{
    int pivot = a[right];
    int i = left - 1;
    for (int j = left; j < right; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[right]);
    return i + 1;
}

void heapify (int a[], int n, int i)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && a[left] > a[largest])
    {
        largest = left;
    }
    if (right < n && a[right] > a[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void merge(int a[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = 0; 
    int *temp = new int[right - left + 1];
    while (i <= mid && j <= right)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = a[i++];
    }
    while (j <= right)
    {
        temp[k++] = a[j++];
    }
    for (int l = 0; l < k; l++)
    {
        a[left + l] = temp[l];
    }
    delete[] temp;
}

void selectionSort(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[min] > a[j])
            {
                min = j;
            }
        }
        swap(a[i], a[min]);
    }
}

void insertionSort(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void bubbleSort(int a[], int n)
{
    for (int size = n; size > 0; size--)
    {
        for (int i = 0; i + 1 < size; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
            }
        }
    }
}

void shakerSort(int a[], int n)
{
    int left = 0, right = n - 1;
    while (left < right)
    {
        for (int i = left; i + 1 < right - left + 1; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
            }
        }
        for (int i = right; i - 1 >= left; i--)
        {
            if (a[i] < a[i - 1])
            {
                swap(a[i], a[i - 1]);
            }
        }
        left++;
        right--;
    }
}

void shellSort(int a[], int n)
{
    for (int gap = n / 2; gap > 1; gap /= 2)
    {
        for(int i = 0; i + gap < n; i++)
        {
            if (a[i] > a[i + gap])
            {
                swap(a[i], a[i + gap]);
            }
        }
    }
    insertionSort(a, n);
}

void heapSort(int a[], int n)
{
    for (int i = n/2 - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        swap(a[i], a[0]);
        heapify(a, i, 0);
    }
}

void mergeSort(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void quickSort(int a[], int left, int right)
{
    if (left < right)
    {
        int pivot = partition(a, left, right);
        quickSort(a, left, pivot - 1);
        quickSort(a, pivot + 1, right);
    }
}

void countingSort(int a[], int n)
{
    int min = a[0], max = a[0], complement;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
        {
            min = a[i];
        }
        if (a[i] > max)
        {
            max = a[i];
        }
    }
    if (min < 0)
    {
        complement = -min;
        int *count = new int [complement + max + 1]();
        for (int i = 0; i < n; i++)
        {
            count[a[i] + complement]++;
        }
        for (int i = 0, j = 0; i < n && j < max + 1; j++)
        {
            while (count[j] > 0)
            {
                a[i++] = j - complement;
                count[j]--;
            }
        }
        delete[] count;    
    }
    else
    {
        int* count = new int [max + 1]();
        for (int i = 0; i < n; i++)
        {
            count[a[i]]++;
        }
        for (int i = 0, j = 0; i < n && j < max + 1; j++)
        {
            while (count[j] > 0)
            {
               a[i++] = j;
               count[j]--; 
            }
        }
        delete[] count;
    }
}

void radixSort(int a[], int n)
{
    int max = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
        }
    }
    for (int expo = 1; max / expo > 0; expo *= 10)
    {
        int count[10] = {0}, *temp = new int [n];
        for (int i = 0; i < n; i++)
        {
            count[a[i] / expo % 10]++;
        }
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            int digit = a[i] / expo % 10;
            temp[--count[digit]] = a[i];
        }
        for (int i = 0; i < n; i++)
        {
            a[i] = temp[i];
        }
        delete[] temp;
    }
}

void flashSort(int a[], int n)
{
    int m = (int)(0.43 * n), min = a[0], max_index = 0, max = a[0], start, end, count = 0;
    int *list = new int [m](), *boundary = new int [m]();
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
        {
            min = a[i];
        }
        if (a[i] > max)
        {
            max_index = i;
            max = a[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        int k = layer(a[i], max, min, m);
        list[k]++;
        boundary[k]++;
    }
    for (int i = 1; i < m; i++)
    {
        list[i] += list[i - 1];
        boundary[i] += boundary[i - 1];
    }
    swap(a[max_index], a[0]);
    int j = 0;
    while (count < n)
    {
        int k = layer(a[j], max, min, m);
        while (j >= list[k])
        {
            j++;
            if (j < n)
            {
                k = layer(a[j], max, min, m);
            }
        }
        int flash = a[j];
        while (j != list[k])
        {
            k = layer(flash, max, min, m);
            int pos = --list[k];
            swap(flash, a[pos]);
            count++;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (i == 0)
        {
            start = 0;
        }
        else
        {
            start = boundary[i - 1]; 
        }
        end = boundary[i] - 1;
        quickSort(a, start, end);
    }
    delete[] list;
}
