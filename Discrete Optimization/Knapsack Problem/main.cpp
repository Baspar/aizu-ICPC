#include <iostream>
#include <vector>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORI(i,z,n) for(int i=z;i<n;i++)
#define MAX(a,b,c) max(a,max(b,c))

using namespace std;

struct Obj {int weight; int value;};

int main () {
    int N, W;
    cin >> N >> W;

    vector<Obj> objects(N);
    FOR(i,N) {
        int v, w;
        cin >> v >> w;
        objects[i] = Obj{w, v};
    }

    vector<int> dyn(W+1);
    dyn[0] = 0;

    FORI(i, 1, W+1)
        for(Obj o: objects)
            if (i >= o.weight)
                dyn[i] = max(dyn[i], dyn[i-o.weight] + o.value);

    cout << dyn[W] << endl;
}
