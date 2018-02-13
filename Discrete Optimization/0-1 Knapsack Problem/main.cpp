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

    vector<vector<int> > dyn(N+1, vector<int>(W+1, 0));

    FOR(i, N)
        FOR(w, W) {
            int x = i+1;
            int y = w+1;
            dyn[x][y] = MAX(
                    dyn[x-1][y],
                    dyn[x][y-1],
                    (objects[i].weight <= y ? dyn[x-1][y-objects[i].weight] + objects[i].value : 0)
                    );
        }

    cout << dyn[N][W] << endl;
}
