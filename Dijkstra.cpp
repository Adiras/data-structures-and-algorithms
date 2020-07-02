#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#define INF 2147483647

using namespace std;

class graph
{
private:
    int vertices;
    vector<pair<int, int>> *adjacency_list;
public:
    graph(int vertices)
    {
        this->vertices = vertices;
        this->adjacency_list = new vector<pair<int, int>>[vertices];
    }

    bool is_edge(int a, int b)
    {
        for (auto & it : adjacency_list[a])
            if (it.first == b) return true;
        return false;
    }

    void add_edge(int a, int b, int w)
    {
        adjacency_list[a].push_back(make_pair(b, w));
        adjacency_list[b].push_back(make_pair(a, w));
    }

    int get_weight(int a, int b)
    {
        for (auto & it : adjacency_list[a])
            if (it.first == b) return it.second;
    }

    int dijkstra(int src, int dst)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
        vector<int> dist(vertices, INF);
        queue.push(make_pair(0, src));
        dist[src] = 0;
        while (!queue.empty()) {
            int u = queue.top().second;
            queue.pop();
            for (auto it = adjacency_list[u].begin(); it != adjacency_list[u].end(); ++it) {
                int v = it->first;
                int weight = it->second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    queue.push(make_pair(dist[v], v));
                }
            }
        }
        return dist[dst];
    }
};

int main()
{
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    pair<int, int> coordinates[n];

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        coordinates[i] = make_pair(x, y);
    }

    int s, d;
    cin >> s >> d;

    vector<pair<int, int>> input_x, input_y;
    for (int i = 0; i < n; ++i) {
        input_x.emplace_back(i, coordinates[i].first);
        input_y.emplace_back(i, coordinates[i].second);
    }

    sort(input_x.begin(), input_x.end(),
         [](const pair<int, int> & a, const pair<int, int> & b) -> bool {
             return a.second < b.second;
         });

    sort(input_y.begin(), input_y.end(),
         [](const pair<int, int> & a, const pair<int, int> & b) -> bool {
             return a.second < b.second;
         });

    graph g(n);

    for (auto it = input_x.begin(); it != input_x.end() - 1; ++it) {
        int a = (it + 0)->first;
        int b = (it + 1)->first;
        int weight = abs((it+0)->second - (it+1)->second);
        g.add_edge(a, b, weight);
    }

    for (auto it = input_y.begin(); it != input_y.end() - 1; ++it) {
        int a = (it + 0)->first;
        int b = (it + 1)->first;
        int weight = abs((it + 0)->second - (it + 1)->second);
        if (g.is_edge(a, b)) {
            if (g.get_weight(a, b) > weight)
                g.add_edge(a, b, weight);
        } else {
            g.add_edge(a, b, weight);
        }
    }

    cout << g.dijkstra(s, d);

    return 0;
}
