#include <iostream>
#include <queue>
#include <vector>

#define FOR(i,n) for(int i=0; i<n; i++)

using namespace std;

struct Edge {int node; int weight;};
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef pair<int, int> PII;

using namespace std;

vector<int> djikstra(Graph g, int v) {
    priority_queue<PII, vector<PII>, greater<PII> > q;

    q.push(PII(0, v));

    vector<int> distances(g.size(), -1);
    vector<bool> seen(g.size(), false);
    distances[v] = 0;
    while (! q.empty()) {
        PII p = q.top();
        q.pop();

        int distance = p.first;
        int node = p.second;
        if (!seen[node]) {
            seen[node] = true;
            for (Edge edge : g[node]) {
                if (distances[edge.node] == -1 || distances[edge.node] > distance + edge.weight) {
                    distances[edge.node] = distance + edge.weight;
                    q.push(PII(distances[edge.node], edge.node));
                }
            }
        }


    }

    return distances;
}

int getFurtherPoint(Graph g, int v) {
    vector<int> minDistances = djikstra(g, v);

    int m = -1;
    int point = -1;
    FOR(i, minDistances.size()) {
        if(minDistances[i] > m) {
            m = minDistances[i];
            point = i;
        }
    }

    return point;
}

int main () {
    int n;
    cin >> n;

    Graph g(n);

    FOR(_, n-1) {
        int s, t, w;
        cin >> s >> t >> w;
        g[s].push_back(Edge{t, w});
        g[t].push_back(Edge{s, w});
    }

    int v1 = getFurtherPoint(g, 0);
    vector<int> d1 = djikstra(g, v1);
    int v2 = getFurtherPoint(g, v1);
    vector<int> d2 = djikstra(g, v2);

    FOR(i, d1.size()) {
        cout << (d1[i] > d2[i] ? d1[i] : d2[i]) << endl;
    }
}
