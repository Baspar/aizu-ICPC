#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#define FOR(i,n) for(unsigned i=0; i<n; i++)

using namespace std;

typedef pair<unsigned, unsigned> point;

int main () {
    unsigned V, E;
    cin >> V >> E;

    set<unsigned> seen;
    seen.insert(0);
    map<unsigned, vector<point> > graph;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    unsigned distance = 0;

    FOR(_, E) {
        unsigned s, t, d;
        cin >> s >> t >> d;
        graph[s].push_back(make_pair(d, t));
        graph[t].push_back(make_pair(d, s));
        if (s == 0) q.push(make_pair(d, t));
        if (t == 0) q.push(make_pair(d, s));
    }

    while (!q.empty() && seen.size() != V) {
        point p = q.top();
        unsigned v = p.second;
        unsigned w = p.first;
        q.pop();

        if (seen.find(v) == seen.end()) {
            seen.insert(v);
            vector<point> neighbours = graph[v];
            FOR(i, neighbours.size()) q.push(neighbours[i]);
            distance += w;
        }
    }

    cout << distance << endl;

}
