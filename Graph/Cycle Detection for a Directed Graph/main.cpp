#include <iostream>
#include <vector>
#include <stack>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORI(i,z,n) for(int i=z;i<n;i++)

using namespace std;

vector<vector<int> > graph;
vector<bool> seen;
vector<bool> localSeen;

bool hasLoop(int i) {
    stack<pair<int, bool> > Q;
    Q.push(make_pair(i, true));
    while (! Q.empty()) {
        auto x = Q.top();
        Q.pop();
        int u = x.first;
        bool goingDown = x.second;

        if (goingDown) {
            if (! seen[u]) {
            Q.push(make_pair(u, false));
            localSeen[u] = true;
            for(int v: graph[u])
                if (localSeen[v])
                    return true;
                else
                    Q.push(make_pair(v, true));
            }
        } else {
            localSeen[u] = false;
            seen[u] = true;
        }

    }
    return false;
}

int main () {
    int V, E;
    cin >> V >> E;

    graph.resize(V);
    seen.resize(V, false);
    localSeen.resize(V, false);

    FOR(i, E) {
        int f, t;
        cin >> f >> t;
        graph[f].push_back(t);
    }

    FOR(i, V)
        if (! seen[i])
            if (hasLoop(i)) {
                cout << 1 << endl;
                return 0;
            }

    cout << 0 << endl;
}
