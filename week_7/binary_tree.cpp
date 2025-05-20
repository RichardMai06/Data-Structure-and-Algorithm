#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
};

NODE *createNode(int data); // done
vector<int> NLR(NODE *pRoot); // done
vector<int> LNR(NODE *pRoot); // done
vector<int> LRN(NODE *pRoot); // done
vector<vector<int>> levelOrder(NODE *pRoot); // done
int countNode(NODE *pRoot); // done
int sumNode(NODE *pRoot); // done
int heightNode(NODE *pRoot, int value); // done
int level(NODE *pRoot, NODE *p); // done
int countLeaf(NODE *pRoot); // done

NODE *createNode(int data)
{
    NODE *new_node = new NODE;
    new_node->key = data;
    new_node->p_left = nullptr;
    new_node->p_right = nullptr;
    return new_node;
}

vector<int> NLR(NODE *pRoot)
{
    vector<int> tree_values;
    if (pRoot == nullptr)
    {
        return tree_values;
    }
    stack<NODE*> tree_nodes;
    tree_nodes.push(pRoot);
    while (!tree_nodes.empty())
    {
        NODE *current = tree_nodes.top();
        int value = current->key;
        tree_values.push_back(value);
        tree_nodes.pop();
        if (current->p_right != nullptr)
        {
            tree_nodes.push(current->p_right);
        }
        if (current->p_left != nullptr)
        {
            tree_nodes.push(current->p_left);
        }
    }
    return tree_values;
}

vector<int> LNR(NODE *pRoot)
{
    vector<int> tree_values;
    if (pRoot == nullptr)
    {
        return tree_values; 
    }
    stack<NODE*> tree_nodes;
    NODE *current = pRoot;
    while (current != nullptr || !tree_nodes.empty())
    {
        while (current != nullptr)
        {
            tree_nodes.push(current);
            current = current->p_left;
        }
        current = tree_nodes.top();
        tree_nodes.pop();
        int value = current->key;
        tree_values.push_back(value);
        current = current->p_right;
    }
    return tree_values;
}

vector<int> LRN(NODE *pRoot)
{
    vector<int> tree_values;
    if (pRoot == nullptr)
    {
        return tree_values;
    }
    stack<NODE*> NRL, LRN;
    NRL.push(pRoot);
    while (!NRL.empty())
    {
        NODE *current = NRL.top();
        NRL.pop();
        LRN.push(current);
        if (current->p_left != nullptr)
        {
            NRL.push(current->p_left);
        }
        if (current->p_right != nullptr)
        {
            NRL.push(current->p_right);
        }
    }
    while (!LRN.empty())
    {
        NODE *current = LRN.top();
        LRN.pop();
        tree_values.push_back(current->key);
    }
    return tree_values;
}

vector<vector<int>> levelOrder(NODE *pRoot)
{
    vector<vector<int>> tree_values;
    if (pRoot == nullptr)
    {
        return tree_values;
    }
    queue<NODE*> tree_nodes;
    tree_nodes.push(pRoot);
    while (!tree_nodes.empty())
    {
        int level_length = tree_nodes.size();
        vector<int> level_values;
        for (int i = 0; i < level_length; i++)
        {
            NODE *current = tree_nodes.front();
            tree_nodes.pop();
            level_values.push_back(current->key);
            if (current->p_left != nullptr)
            {
                tree_nodes.push(current->p_left);
            }
            if (current->p_right != nullptr)
            {
                tree_nodes.push(current->p_right);
            }
        }
    }
    return tree_values;
}

int countNode(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    vector<int> tree_values = NLR(pRoot);
    return tree_values.size();
}

int sumNode(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    vector<int> tree_values = NLR(pRoot);
    int sum = 0;
    for (int x : tree_values)
    {
        sum += x;
    }
    return sum;
}

int heightNode(NODE *pRoot, int value)
{
    if (pRoot == nullptr)
    {
        return -1;
    }
    vector<vector<int>> tree_values = levelOrder(pRoot);
    int height = -1;
    for (int i = tree_values.size(); i >= 0; i--)
    {
        for (int key : tree_values[i])
        {
            if (value == key)
            {
                height = i;
            }
        }
    }
    return height;
}

int level(NODE *pRoot, NODE *p)
{
    if (pRoot ==  nullptr)
    {
        return -1;
    }
    vector<vector<int>> tree_values = levelOrder(pRoot);
    int level = -1;
    for (int i = 0; i < tree_values.size(); i++)
    {
        for (int value : tree_values[i])
        {
            if (value == p->key)
            {
                level = i;
            }
        }
    }
    return level;
}

int countLeaf(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    stack<NODE*> tree_nodes;
    int leaf = 0;
    tree_nodes.push(pRoot);
    while (!tree_nodes.empty())
    {
        NODE *current = tree_nodes.top();
        tree_nodes.pop();
        if (current->p_left == nullptr && current->p_right == nullptr)
        {
            leaf++;
            continue;
        }
        else if (current->p_right != nullptr)
        {
            tree_nodes.push(current->p_right);
        }
        else if (current->p_left != nullptr)
        {
            tree_nodes.push(current->p_left);
        }
    }
    return leaf;
}
