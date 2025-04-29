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

struct Stack
{
    NODE *top;
};

Stack *initializeStack();
void push(Stack *&s, int key);
int pop(Stack *&s);
int size(Stack *s);
bool isEmpty(Stack *s);

NODE *createNode(int data)
{
    NODE *new_node = new NODE;
    new_node->key = data;
    new_node->p_next = nullptr;
    return new_node;
}

Stack *initializeStack()
{
    Stack *s = new Stack;
    s->top = nullptr;
    return s;
}

void push(Stack *&s, int key)
{
    NODE *new_node = createNode(key);
    if (s->top == nullptr)
    {
        s->top = new_node;
    }
    else
    {
        new_node->p_next = s->top;
        s->top = new_node;
    }
}

int pop(Stack *&s)
{
    if (s->top == nullptr)
    {
        return -1;
    }
    NODE *pop = s->top;
    int num = pop->key;
    s->top = s->top->p_next;
    delete pop;
    return num;
}

int size(Stack *s)
{
    int size = 0;
    NODE *current = s->top;
    while (current != nullptr)
    {
        size++;
        current = current->p_next;
    }
    return size;
}

bool isEmpty(Stack *s)
{
    if (s->top == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printStack(ofstream &f, NODE *node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->p_next != nullptr)
    {
        printStack(f, node->p_next);
    }
    f << node->key << " ";
}

void removeStack(Stack *&s)
{
    while (!isEmpty(s))
    {
        pop(s);
    }
    delete s;
    s = nullptr;
}

int main()
{
    ifstream fin("input_stack.txt");
    ofstream fout("output_stack.txt");
    if (!fin.is_open() || !fout.is_open())
    {
        cerr << "Cannot open file." << endl;
        exit(4);
    }
    else
    {
        Stack *stack;
        string line, command;
        while (getline(fin, line))
        {
            stringstream stream(line);
            stream >> command;
            if (command == "init")
            {
                stack = initializeStack();
                if(isEmpty(stack))
                {
                    fout << "EMPTY" << endl;
                }
                else
                {
                    cerr << "Error in initializing stack." << endl;
                    exit(1);
                }
            }
            else if (command == "push")
            {
                int value, length_old, length_new;
                length_old = size(stack);
                stream >> value;
                push (stack, value);
                length_new = size(stack);
                if (length_new == length_old)
                {
                    cerr << "Error in pushing values." << endl;
                    exit(2);
                }
                else
                {
                    printStack(fout, stack->top);
                    fout << endl;
                }
            }
            else if (command == "pop")
            {
                int length_old, length_new;
                length_old = size(stack);
                pop(stack);
                length_new = size(stack);
                if (length_new != 0 && length_old != 0 && length_new == length_old)
                {
                    cerr << "Error in popping values." << endl;
                    exit(3);
                }
                else
                {
                    if (isEmpty(stack))
                    {
                        fout << "EMPTY" << endl;
                    }
                    else
                    {
                        printStack(fout, stack->top);
                        fout << endl;
                    }
                }
            }
            else
            {
                cerr << "No command" << endl;
            }
        }
        fin.close();
        fout.close();
        removeStack(stack);    
    }
    return 0;
}
