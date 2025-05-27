#include <vector>
using namespace std;

struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
    int height;
};

NODE* createNode(int data);
void insert(NODE *pRoot, int x);
void remove(NODE *pRoot, int x);
bool isAVL(NODE *pRoot);

NODE* createNode(int data)
{
    NODE *new_node = new NODE;
    new_node->key = data;
    new_node->height = 0;
    new_node->p_left = nullptr;
    new_node->p_right = nullptr;
    return new_node;
}
