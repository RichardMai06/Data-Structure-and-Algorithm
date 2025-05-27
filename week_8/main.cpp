#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

vector<vector<int>> convertMatrixToList(const string &filename); 
vector<vector<int>> convertListToMatrix(const string &filename); 
bool isDirected(const vector<vector<int>> &adjMatrix); 
int countVertices(const vector<vector<int>> &adjMatrix); 
int countEgdes(const vector<vector<int>> &adjMatrix); 
vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix); 
bool isCompleteGraph(const vector<vector<int>> &adjMatrix); 
bool isBipartite(const vector<vector<int>> &adjMatrix); 
bool isCompleteBipartite(const vector<vector<int>> &adjMatrix); 
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>> &adjMatrix); 
vector<vector<int>> getComplementGraph(const vector<vector<int>> &adjMatrix); 
vector<int> findEulerCycle(const vector<vector<int>> &adjMatrix); 
vector<vector<int>> dfsSpanningTree(const vector<vector<int>> &adjMatrix, int start);
vector<vector<int>> bfsSpanningTree(const vector<vector<int>> &adjMatrix, int start);
bool isConnected(int u, int v, const vector<vector<int>> &adjMatrix);
vector<int> dijkstra(int start, int end, vector<vector<int>> &adjMatrix);
vector<int> bellmanFord(int start, int end, vector<vector<int>> &adjMatrix);

vector<vector<int>> convertMatrixToList(const string &filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cerr << "Cannot open file." << endl;
        exit(1);
    }
    else
    {
        vector<vector<int>> list;
        int size;
        fin >> size;
        for (int i = 0; i < size; i++)
        {
            vector<int> row_values;
            int count = 0;
            for (int j = 0; j < size; j++)
            {
                int value;
                fin >> value;
                if (value == 0)
                {
                    continue;
                }
                else if (value == 1)
                {
                    count++;
                    row_values.push_back(j);
                }
            }
            if (count == 0)
            {
                row_values.push_back(0);
            }
            else
            {
                row_values.insert(row_values.begin(), count);
            }
            list.push_back(row_values);
        }
        fin.close();
        return list;
    }
}

vector<vector<int>> convertListToMatrix(const string &filename)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cerr << "Cannot open file." << endl;
        exit(1);
    }
    else
    {
        vector<vector<int>> matrix;
        int size;
        fin >> size;
        for (int i = 0; i < size; i++)
        {
            vector<int> row(size, 0);
            int count;
            fin >> count;
            while (count > 0)
            {
                int j;
                fin >> j;
                row[j] = 1;
                count--;
            }
            matrix.push_back(row);
        }
        fin.close();
        return matrix;
    }
}

bool isDirected(const vector<vector<int>> &adjMatrix)
{
    bool indirected = true;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int j = 0; j < adjMatrix[i].size(); j++)
        {
            if (adjMatrix[i][j] != adjMatrix[j][i])
            {
                return true;
            }
        }
    }
    return false;
}

int countVertices(const vector<vector<int>> &adjMatrix)
{
    return adjMatrix.size();
}

int countEgdes(const vector<vector<int>> &adjMatrix)
{
    int count = 0;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            if (adjMatrix[i][j] == 1)
            {
                count++;
            }
        }
    }
    count = (isDirected(adjMatrix)) ? count : count / 2;
    return count;
}

vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix)
{
    vector<int> isolated_vetices;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        bool connect = false;
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1)
            {
                connect = true;
                break;
            }
        }
        if (connect == false)
        {
            isolated_vetices.push_back(i);
        }
    }
    return isolated_vetices;
}

bool isCompleteGraph(const vector<vector<int>> &adjMatrix)
{
    vector<int> isolated_vertices = getIsolatedVertices(adjMatrix);
    if(isolated_vertices.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isBipartite(const vector<vector<int>> &adjMatrix)
{
    int vertices_num = countVertices(adjMatrix);
    vector<int> color(vertices_num, -1);
    queue<int> vertices;
    for (int i = 0; i < vertices_num; i++)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            vertices.push(i);
            while (!vertices.empty())
            {
                int vertex = vertices.front();
                vertices.pop();
                for (int j = 0; j < vertices_num; j++)
                {
                    if (adjMatrix[vertex][j] == 1)
                    {
                        if (color[j] == -1)
                        {
                            color[j] = 1 - color[vertex];
                            vertices.push(j);
                        }
                        else if (color[vertex] == color[j])
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>> &adjMatrix)
{
    int vertices_num = countVertices(adjMatrix);
    vector<int> color(vertices_num, -1), set_1, set_2;
    queue <int> vertices;
    for (int i = 0; i < vertices_num; i++)
    {
        if (color[i] == -1)
        {
            color[i] = 0;
            vertices.push(i);
            while (!vertices.empty())
            {
                int vertex = vertices.front();
                vertices.pop();
                for (int j = 0; j < vertices_num; j++)
                {
                    if (adjMatrix[vertex][j] == 1)
                    {
                        if (color[j] == -1)
                        {
                            color[j] = 1 - color[vertex];
                            vertices.push(j);
                        }
                        else if (color[vertex] == color[j])
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < vertices_num; i++)
    {
        if (color[i] == 0)
        {
            set_1.push_back(i);
        }
        else
        {
            set_2.push_back(i);
        }
    }
    for (int u : set_1)
    {
        for (int v : set_2)
        {
            if (adjMatrix[u][v] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>> &adjMatrix)
{
    vector<vector<int>> matrix;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        vector<int> row;
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1)
            {
                row.push_back(1);
            }
            else 
            {
                row.push_back(0);
            }
        }
        matrix.push_back(row);
    }
    return matrix;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>> &adjMatrix)
{
    vector<vector<int>> matrix;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        vector<int> row;
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            if (i == j || adjMatrix[i][j] == 1)
            {
                row.push_back(0);
            }
            else
            {
                row.push_back(1);
            }
        }
        matrix.push_back(row);
    }
    return matrix;
}

vector<int> findEulerCycle(const vector<vector<int>> &adjMatrix)
{
    vector<int> euler_cycle;
    vector<vector<int>> matrix = adjMatrix;
    int vertices_num = countVertices(adjMatrix);
    if (isDirected(adjMatrix))
    {
        for (int i = 0; i < vertices_num; i++)
        {
            int degree_in = 0, degree_out = 0;
            for (int j = 0; j < vertices_num; j++)
            {
                degree_in += (adjMatrix[j][i] == 1) ? 1 : 0;
                degree_out += (adjMatrix[i][j] == 1) ? 1 : 0;
            } 
            if (degree_out != degree_in)
            {
                return euler_cycle;
            }
        }
        stack<int> went_vertices;
        went_vertices.push(0);
        while (!went_vertices.empty())
        {
            int vertex = went_vertices.top();
            bool moved = false;
            for (int move_to = 0; move_to < vertices_num; move_to++)
            {
                if (matrix[vertex][move_to] == 1)
                {
                    matrix[vertex][move_to] = 0;
                    went_vertices.push(move_to);
                    moved = true;
                    break;
                }
            }
            if (!moved)
            {
                euler_cycle.push_back(vertex);
                went_vertices.pop();
            }
        }
    }
    else
    {
        for (int i = 0; i < vertices_num; i++)
        {
            int degree = 0;
            for (int j = 0; j < vertices_num; j++)
            {
                degree += (adjMatrix[i][j] == 1) ? 1 : 0;
            }
            if (degree % 2 == 1)
            {
                return euler_cycle;
            }
        }
        stack<int> went_vertices;
        went_vertices.push(0);
        while (!went_vertices.empty())
        {
           int vertex = went_vertices.top();
           bool moved = false;
           for (int move_to = 0; move_to < vertices_num; move_to++)
           {
                if (matrix[vertex][move_to] == 1)
                {
                    matrix[vertex][move_to] = 0;
                    matrix[move_to][vertex] = 0;
                    went_vertices.push(move_to);
                    moved = true;
                    break;
                }
           }
           if (!moved)
           {
                euler_cycle.push_back(vertex);
                went_vertices.pop();
           }
        }
    }
    for (int i = 0, j = euler_cycle.size() - 1; i < j; i++, j--)
    {
        int temp = euler_cycle[i];
        euler_cycle[i] = euler_cycle[j];
        euler_cycle[j] = temp;
    }
    return euler_cycle;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>> &adjMatrix, int start)
{
    int vertices_num = countVertices(adjMatrix);
    vector<bool> went(vertices_num, false);
    vector<vector<int>> tree(vertices_num);
    stack<int> vertices;
    vertices.push(start);
    went[start] = true;
    while (!vertices.empty())
    {
        int vertex = vertices.top();
        vertices.pop();
        if (!went[vertex])
        {
            went[vertex] = true;
        }
        for (int move_to = vertices_num - 1; move_to >= 0; move_to--)
        {
            if (adjMatrix[vertex][move_to] == 1 && !went[move_to])
            {
                vertices.push(move_to);
                tree[vertex].push_back(move_to);
                tree[move_to].push_back(vertex);
            }
        }
    }
    return tree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>> &adjMatrix, int start)
{
    int vertices_num = countVertices(adjMatrix);
    vector<bool> went(vertices_num, false);
    vector<vector<int>> tree(vertices_num);
    queue<int> vertices;
    vertices.push(start);
    went[start] = true;
    while(!vertices.empty())
    {
        int vertex = vertices.front();
        vertices.pop();
        for (int move_to = 0; move_to < vertices_num; move_to++)
        {
            if (adjMatrix[vertex][move_to] == 1 && !went[move_to])
            {
                vertices.push(move_to);
                went[move_to] = true;
                tree[vertex].push_back(move_to);
                tree[move_to].push_back(vertex);
            }
        }
    }
    return tree;
}

bool isConnected(int u, int v, const vector<vector<int>> &adjMatrix)
{
    int vertices_num = countVertices(adjMatrix);
    vector<bool> went(vertices_num, false);
    queue<int> vertices;
    vertices.push(u);
    went[u] = true;
    while (!vertices.empty())
    {
        int vertex = vertices.front();
        vertices.pop();
        if (vertex == v)
        {
            return true;
        }
        for (int move_to = 0; move_to < vertices_num; move_to++)
        {
            if (adjMatrix[vertex][move_to] == 1 && !went[move_to])
            {
                vertices.push(move_to);
                went[move_to] = true;
            }
        }
    }
    return false;
}