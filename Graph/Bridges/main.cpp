#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#define FOR(i,n) for(int i=0; i<n; i++)

using namespace std;
struct Edge {
    int u;
    int v;
};
bool operator< (const Edge& e1, const Edge& e2) {
    return e1.u < e2.u || (e1.u == e2.u && e1.v < e2.v);
};
typedef vector<vector<int> > Graph;

void DFS(Graph &g, int u, int &clock, vector<int> &low, vector<int> &disc, vector<bool> &seen, vector<int> &parent, vector<Edge> &bridges) {
    stack<int> s;
    for(int v: g[u]) {
        if (! seen[v]) {
            clock++;

            disc[v] = clock;
            low[v] = clock;
            seen[v] = true;
            parent[v] = u;

            DFS(g, v, clock, low, disc, seen, parent, bridges);

            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u])
                bridges.push_back(Edge{min(u, v), max(u, v)});
        } else if (v != parent[u]) {
            low[u]  = min(low[u], disc[v]);
        }
    }
}

int main () {
    int V, E;
    cin >> V >> E;

    Graph g(V);
    vector<Edge> bridges;

    FOR(i,E) {
        int s, t;
        cin >> s >> t;

        g[s].push_back(t);
        g[t].push_back(s);
    }
    int clock = 2;
    vector<int> low(V, 0);
    vector<int> disc(V, 0);
    vector<int> parent(V, -1);
    vector<bool> seen(V, false);
    disc[0] = 1;
    low[0] = 1;
    seen[0] = true;

    DFS(g, 0, clock, low, disc, seen, parent, bridges);

    sort(bridges.begin(), bridges.end());

    for(Edge e: bridges)
        cout << e.u << " " << e.v << endl;
}
