#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, double> id;
typedef pair<double, int> di;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<double> vd;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<vii> vvii;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<id> vid;
typedef vector<vd> vvd;
typedef vector<vid> vvid;
typedef vector<vll> vvll;

#define LSOne(S) (S & (-S))
#define pb push_back
#define ctz __builtin_ctz
#define popcount __builtin_popcount

const double PI = 2*acos(0.0)


#define EPS 1e-9

struct point{ double x, y;
    point() {x = y = 0;}
    point(double _x, double _y): x(_x), y(_y) {}
    bool operator < (point other) const {
        // sort by x-coord, break ties with y-coord
        if (fabs(x-other.x) > EPS) {
            return x < other.x;
        } else {
            return y < other.y;
        }
        }
    bool operator == (point other) {
        return fabs(x - other.x) < EPS && fabs(y - other.y) < EPS;
    }
};

double dist(point p1, point p2) {
    return hypot(p1.x-p2.x, p1.y-p2.y);
}


double M[205][205];
point cannons[205];
int n;

int main() {
    point start, end;
    scanf("%lf %lf",&start.x, &start.y);
    scanf("%lf %lf",&end.x, &end.y);

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lf %lf", &cannons[i].x, &cannons[i].y);
    }

    cannons[n] = end;

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            double d = dist(cannons[i], cannons[j]);
            double walk = d/5;
            double fire = 2 + fabs(50.0 - d)/2;
            M[i][j] = min(walk, fire);
        }
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++) {
            for(int j=0;j<=n;j++) {
                M[i][j] = min(M[i][j], MP[i][k]+MP[k][j]);
            }
        }
    }

    double best = dist(start, end)/5;
    for(int i=0;i<n;i++) {
        double curr = dist(start, cannons[i])/5 + M[i][n];
        best = min(curr, best);
    }
    printf("%f\n", best);
}