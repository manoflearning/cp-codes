#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 404;
const int MAXM = 10101;

struct UF {
    vector<int> uf;
    void build(int n) {
        uf.clear();
        uf.resize(n + 1, -1);
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] = V;
    }
}uf;

int N, M, F;
struct Edge { int u, v; ll c, t; };
vector<Edge> e;

void input() {
    cin >> N >> M >> F;
    e.resize(M);
    for (auto& i : e) {
        cin >> i.u >> i.v >> i.c >> i.t;
    }
}

void bs() {
    double l = 0, r = F;
    for (int i = 0; i < 60; i++) {
        uf.build(N);

        double mid = (l + r) / 2;
        sort(all(e), [&](const Edge& e1, const Edge& e2) {
            return mid * e1.t + e1.c < mid * e2.t + e2.c;
        });

        double sum = 0;

        for (auto& j : e) {
            if (uf.find(j.u) == uf.find(j.v)) continue;
            uf.merge(j.u, j.v);
            sum += mid * j.t + j.c;
        }

        if (sum <= F) l = mid;
        else r = mid;
    }

    cout << fixed;
    cout.precision(4);
    cout << l;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    bs();
}