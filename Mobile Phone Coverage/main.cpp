#include <iostream>
#include <stdio.h>
#include <math.h>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<double, double> squareCorner;
typedef pair<squareCorner, squareCorner> squareCorners;

double totalLength (vector<squareCorners> squares, double x) {
    // Ignore squares not crossing the ray line
    for(vector<squareCorners>::iterator it = squares.begin(); it!=squares.end(); it++) {
        double x0 = it->first.first;
        double x1 = it->second.first;
        if (x < x0 || x >= x1) {
            squares.erase(it);
            it--;
        }
    }

    // Add y[01] to a list
    vector<pair<double, bool> > ys;
    for(unsigned i=0; i<squares.size(); i++) {
        squareCorners p = squares[i];
        double y0 = p.first.second;
        double y1 = p.second.second;
        ys.push_back(make_pair(y0, true));
        ys.push_back(make_pair(y1, false));
    }

    // Sort list
    sort(ys.begin(), ys.end());

    // Compute sum distance
    int beginning = 0;
    double l = 0;
    double startSegment = 0.;
    for(unsigned i=0; i<ys.size(); i++) {
        pair<double, bool> p = ys[i];
        bool isBeginning = p.second;
        double y = p.first;

        if (beginning == 0)
            startSegment = y;
        beginning += isBeginning ? 1 : -1;
        if (beginning == 0)
            l += y - startSegment;
    }

    return l;
}

int main () {
    int N;
    cin >> N;
    int cpt = 0;

    // Read info for one Problem
    while (N != 0) {
        cpt++;
        vector<squareCorners> squares;
        set<double> xs;

        // Read info about each antenna
        for (int i=0; i<N; i++) {
            double cx, cy, r;
            cin >> cx >> cy >> r;
            double x0 = cx - r,
                   x1 = cx + r,
                   y0 = cy - r,
                   y1 = cy + r;
            xs.insert(x0);
            xs.insert(x1);
            squares.push_back(make_pair(make_pair(x0, y0), make_pair(x1, y1)));
        }

        double area = 0.;
        set<double>::iterator it=xs.begin();
        double prevY = *it;
        double prevWidth = totalLength(squares, prevY);
        it++;
        while (it != xs.end()) {
            area += prevWidth * (*it - prevY);
            prevY = *it;
            prevWidth = totalLength(squares, *it);
            it++;
        }

        area = round(area*100)/100;

        printf("%d %.2f\n", cpt, area);
        cin >> N;
    }
}
