#include <vector>
using namespace std;

struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
};

NODE* createNode(int data); // done
NODE* search(NODE *pRoot, int x); // done
void insert(NODE *pRoot, int x); // done
void remove(NODE *pRoot, int x);
NODE* createTree(int a[], int n); // done
void removeTree(NODE *pRoot);
int height(NODE *pRoot);
int countLess(NODE *pRoot, int x);
int countGreater(NODE *pRoot, int x);
bool isBST(NODE *pRoot);
bool isFullBST(NODE *pRoot);

NODE* createNode(int data)
{
    NODE *new_node = new NODE;
    new_node->key = data;
    new_node->p_left = nullptr;
    new_node->p_right = nullptr;
    return new_node;
}

NODE* search(NODE *pRoot, int x)
{
    NODE *current = pRoot;
    while (current != nullptr)
    {
        if (current->key == x)
        {
            return current;
        }
        else if (x > current->key)
        {
            current = current->p_right;
        }
        else
        {
            current = current->p_left;
        }
    }
    return nullptr;
}

void insert(NODE *pRoot, int x)
{
    if (pRoot = nullptr)
    {
        pRoot = createNode(x);
        return;
    }
    NODE *current = pRoot;
    while (current != nullptr)
    {
        if (x = current->key)
        {
            return;
        }
        if (x > current->key && current->p_right == nullptr)
        {
            NODE *new_node = createNode(x);
            current->p_right = new_node;
            return;
        }
        else if (x > current->key)
        {
            current = current->p_right;
        }
        if (x < current->key && current->p_left == nullptr)
        {
            NODE * new_node = createNode(x);
            current->p_left = new_node;
            return;
        }
        else if (x < current->key)
        {
            current = current->p_left;
        }
    }
}

NODE* createTree(int a[], int n)
{
    NODE *pRoot = nullptr;
    for (int i = 0; i < n; i++)
    {
        insert(pRoot, a[i]);
    }
    return pRoot;
}