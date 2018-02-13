#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#define FOR(i,n) for(unsigned i=0; i<n; i++)

using namespace std;

struct Edge {unsigned node; unsigned weight;};
struct FullEdge {unsigned from; unsigned to; unsigned weight;};
typedef map<int, vector<Edge> > Graph;

vector<FullEdge> findSmallestEdges(Graph inEdges, unsigned r) {
    vector<FullEdge> smallestEdges;
    for(auto it=inEdges.begin(); it!=inEdges.end(); it++) {
        unsigned i = it->first;
        if (i != r) {
            Edge minEdge = it->second[0];
            FOR(j, it->second.size())
                if (it->second[j].weight < minEdge.weight)
                    minEdge = it->second[j];
            smallestEdges.push_back(FullEdge{minEdge.node, i, minEdge.weight});
        }
    }
    return smallestEdges;
}

unsigned findACircuit(vector<FullEdge> tree, unsigned r) {
    vector<unsigned> init, running;
    map<unsigned, unsigned> mTree;
    mTree[r] = r;
    for(FullEdge edge : tree) {
        init.push_back(edge.to);
        running.push_back(edge.to);
        mTree[edge.to] = edge.from;
    }

    FOR(_, tree.size())
        FOR(i, running.size()) {
            unsigned edge = running[i];
            unsigned newEdge = mTree[edge];
            if (newEdge != r && newEdge == init[i])
                return newEdge;
            running[i]=newEdge;
        }

    return r;
}

void contractCycle(Graph &inEdges, vector<FullEdge> tree, unsigned startCircuit, unsigned &newPoint) {
    // Init
    map<unsigned, Edge> mTree;
    set<unsigned> cycleEdges;
    for(FullEdge edge : tree) {
        mTree[edge.to] = Edge{edge.from, edge.weight};
        cycleEdges.insert(edge.from);
    }

    for(auto it = inEdges.begin(); it != inEdges.end(); it++) {
        if (cycleEdges.find(it->first) != cycleEdges.end()) {
        }
    }

    // Increment newPoint
    newPoint++;
}

unsigned getWeightCycle(vector<FullEdge> tree, unsigned startCircuit) {
    map<unsigned, Edge> mTree;
    for(FullEdge edge : tree) mTree[edge.to] = Edge{edge.from, edge.weight};

    unsigned weight = 0;
    Edge i = Edge{startCircuit, 0};
    do {
        i = mTree[i.node];
        weight += i.weight;
    } while (i.node != startCircuit);

    return weight;
}

int main () {
    unsigned V, E, r;
    cin >> V >> E >> r;

    Graph inEdges;

    FOR(_, E) {
        unsigned s, t, w;
        cin >> s >> t >> w;
        inEdges[t].push_back(Edge{s, w});
    }

    unsigned weight = 0;
    vector<FullEdge> smallestEdges = findSmallestEdges(inEdges, r);
    unsigned startCircuit = findACircuit(smallestEdges, r);
    while (startCircuit != r) {
        weight += getWeightCycle(smallestEdges, startCircuit);
        contractCycle(inEdges, smallestEdges, startCircuit, V);
        smallestEdges = findSmallestEdges(inEdges, r);
        startCircuit = findACircuit(smallestEdges, r);
    }

    for(FullEdge e : smallestEdges) weight += e.weight;

    cout << weight << endl;
}
