#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#define FOR(i,n) for(int i=0; i<n; i++)

using namespace std;
typedef vector<vector<int> > Graph;

void DFS(Graph &g, int u, int &clock, vector<int> &low, vector<int> &disc, vector<bool> &seen, vector<int> &parent, vector<bool> &ap) {
    int children = 0;
    for(int v: g[u]) {
        children++;
        if (! seen[v]) {
            clock++;

            disc[v] = clock;
            low[v] = clock;
            seen[v] = true;
            parent[v] = u;

            DFS(g, v, clock, low, disc, seen, parent, ap);

            low[u] = min(low[u], low[v]);

            if (parent[u] == -1 && children > 1)
                ap[u] = true;
            if (parent[u] != -1 && low[v] >= disc[u])
                ap[u] = true;

        } else if (v != parent[u]) {
            low[u]  = min(low[u], disc[v]);
        }
    }
}

int main () {
    int V, E;
    cin >> V >> E;

    Graph g(V);
    vector<bool> ap(V, false);

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

    DFS(g, 0, clock, low, disc, seen, parent, ap);

    FOR(i, V)
        if (ap[i])
            cout << i << endl;
}
