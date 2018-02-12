#include <iostream>
#include <vector>
#include <stack>

#define FOR(i,n) for(int i=0;i<n;i++)

using namespace std;

vector<vector<int> > graph;
vector<vector<int> > invGraph;
vector<bool> seen;
vector<int> rootGroup;
stack<int> vStack;

void makeStack(int u) {
    seen[u] = true;
    for(int v: graph[u])
        if (! seen[v])
            makeStack(v);
    vStack.push(u);
}

void getConnectedCompRecur(int u, int root) {
    if (rootGroup[u] == -1) {
        rootGroup[u] = root;
        for(int v: invGraph[u])
            getConnectedCompRecur(v, root);
    }
}

void getConnectedComp() {
    while (! vStack.empty()) {
        int u = vStack.top();
        vStack.pop();
        getConnectedCompRecur(u, u);
    }
}

int main () {
    int V, E;
    cin >> V >> E;

    graph.resize(V);
    invGraph.resize(V);
    seen.resize(V, false);
    rootGroup.resize(V, -1);

    FOR(i,E) {
        int s, t;
        cin >> s >> t;

        graph[s].push_back(t);
        invGraph[t].push_back(s);
    }

    FOR(i, V)
        if (! seen[i]) makeStack(i);

    getConnectedComp();

    int Q;
    cin >> Q;
    FOR(i,Q) {
        int f, t;
        cin >> f >> t;
        cout << (rootGroup[f] == rootGroup[t]) << endl;
    }
}
