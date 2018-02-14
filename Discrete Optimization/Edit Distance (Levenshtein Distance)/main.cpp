#include <iostream>
#include <vector>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORI(i,z,n) for(int i=z;i<n;i++)

using namespace std;

int main () {
    string s1, s2;
    cin >> s1;
    cin.ignore();
    cin >> s2;

    vector<vector<int> > dyn = vector<vector<int> >(s1.length()+1, vector<int>(s2.length()+1, 0));

    FOR(i, s1.length()+1) dyn[i][0] = i;
    FOR(i, s2.length()+1) dyn[0][i] = i;

    FOR(i, s1.length()) {
        FOR(j, s2.length()) {
            int x = i+1;
            int y = j+1;

            int m = s1.length() + s2.length();
            if (s1[i] == s2[j]) {
                // Same last letter
                m = min(m, dyn[x-1][y-1]);
            }

            // Add/sub letters
            m = min(m, dyn[x-1][y] + 1);
            m = min(m, dyn[x][y-1] + 1);

            // Substitute letters
            m = min(m, dyn[x-1][y-1] + 1);

            dyn[x][y] = m;
        }
    }

    cout << dyn[s1.length()][s2.length()] << endl;
}
