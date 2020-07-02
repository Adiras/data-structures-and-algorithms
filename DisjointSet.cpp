#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class DisjointSet
{
private:
    int* parent;
    int capacity;

public:
    DisjointSet(int capacity)
    {
        this->capacity = capacity;
        this->parent = new int[capacity];

        for (int i = 0; i < capacity; i++)
            parent[i] = -1;
    }

    int FIND(int i)
    {
        if (parent[i] == -1) 
            return i;
        return FIND(parent[i]);
    }

    void UNION(int x, int y)
    {
        int a = FIND(x);
        int b = FIND(y);
        if (a != b)
            parent[a] = b;
    }
};

class Graph
{
private:
    list<int>* adjLists;
    int numVertices;

public:
    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        this->adjLists = new list<int> [numVertices];
    }

    void addEdge(int i, int j)
    {
        adjLists[i].push_back(j);
    }

    bool hasEdge(int i, int j)
    {
        for (auto const& v : adjLists[i])
        {
            if (v == j)
                return true;
        }
        return false;
    }

    bool hasCycle()
    {
        DisjointSet set(numVertices);

        for (int i = 0; i < numVertices; i++)
        {
            for (auto const& j : adjLists[i])
            {
                int x = set.FIND(i);
                int y = set.FIND(j);

                if (x == y)
                    return true;

                set.UNION(x, y);
            }
        }
        return false;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    Graph graph(n);

    map<int, int> persons;

    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> m;
        for (int ignore = 0; ignore < m; ignore++)
        {
            int x;
            cin >> x;

            if (persons.find(x) != persons.end())
            {
                graph.addEdge(persons.at(x), i);
            }
            persons[x] = i;
        }
    }

    if (persons.size() == 1)
    {
        graph.addEdge(0, n-1);  // jeżeli graf jest linią łączymy ostatnią krawędź z pierwszą
    }

    if (graph.hasCycle())
        cout << "TAK";
    else
        cout << "NIE";

    return 0;
}
