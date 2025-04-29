#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct NODE
{
    int key;
    NODE *p_next;
};

struct Queue
{
    NODE *head;
    NODE *tail;
};

Queue *initializeQueue();
void push(Queue *&q, int key);
int pop(Queue *&q);
int size(Queue *q);
bool isEmpty(Queue *q);

NODE *createNode(int data)
{
    NODE *new_node = new NODE;
    new_node->key = data;
    new_node->p_next = nullptr;
    return new_node;
}

Queue *initializeQueue()
{
    Queue *q = new Queue;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}

void enqueue(Queue *&q, int key)
{
    NODE *new_node = createNode(key);
    if (q->head == nullptr)
    {
        q->head = new_node;
        q->tail = new_node;
    }
    else
    {
        q->tail->p_next = new_node;
        q->tail = new_node;
    }
}

int dequeue(Queue *&q)
{
    if (q->head == nullptr)
    {
        return -1;
    }
    else if (q->head == q->tail)
    {
        NODE *current = q->head;
        int num = current->key;
        q->head = nullptr;
        q->tail = nullptr;
        delete current;
        return num;
    }
    else
    {
        NODE *current = q->head;
        int num = current->key;
        q->head = current->p_next;
        delete current;
        return num;
    }
}

int size(Queue *q)
{
    NODE *current = q->head;
    int size = 0;
    while (current != nullptr)
    {
        size++;
        current = current->p_next;
    }
    return size;
}

bool isEmpty(Queue *q)
{
    if (q->head == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printQueue(ofstream &f, Queue *q)
{
    NODE *current = q->head;
    while (current != nullptr)
    {
        f << current->key << " ";
        current = current->p_next;
        if (current == nullptr)
        {
            f << endl;
        }
    }
}

void removeQueue(Queue *&q)
{
    while (q->head != nullptr)
    {
        dequeue(q);
    }
    delete q;
    q = nullptr;
}

int main()
{
    ifstream fin("input_queue.txt");
    ofstream fout("output_queue.txt");
    if (!fin.is_open() || !fout.is_open())
    {
        cerr << "Cannot open file." << endl;
        exit(4);
    }
    else 
    {
        Queue *queue;
        string line, command;
        while (getline(fin, line))
        {
            stringstream stream(line);
            stream >> command;
            if (command == "init")
            {
                queue = initializeQueue();
                if (isEmpty(queue))
                {
                    fout << "EMPTY" << endl;
                }
                else
                {
                    cerr << "Error in initializing queue." << endl;
                    exit(1);
                }
            }
            else if (command == "enqueue")
            {
                int length_old, length_new, value;
                length_old = size(queue);
                stream >> value;
                enqueue(queue, value);
                length_new = size(queue);
                if (length_new == length_old)
                {
                    cerr << "Error in enqueueing values." << endl;
                    exit(2);
                }
                else
                {
                    printQueue(fout, queue);
                }
            }
            else if (command == "dequeue")
            {
                int length_old, length_new;
                length_old = size(queue);
                dequeue(queue);
                length_new = size(queue);
                if (length_new != 0 && length_old != 0 && length_new == length_old)
                {
                    cerr << "Error in dequeueing values." << endl;
                    exit(3);
                }
                else
                {
                    if (isEmpty(queue))
                    {
                        fout << "EMPTY" << endl;
                    }
                    else
                    {
                        printQueue(fout, queue);
                    }
                }
            }
            else
            {
                cerr << "No command." << endl;
            }
        }
        fin.close();
        fout.close();
        removeQueue(queue);
    }
    return 0;
}