#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

vector<int> p(1010, -1);

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    p[U] += p[V];
    p[V] = U;
}

int n, m, vi[1010], e[1010];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(e, -1, sizeof(e));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        char op; int u, v;
        cin >> op >> u >> v;
        if (op == 'F') merge(u, v);
        else {
            if (e[u] == -1) e[u] = v;
            else merge(v, e[u]);
            if (e[v] == -1) e[v] = u;
            else merge(u, e[v]);
        }
    }

    set<int> s;
    for (int v = 1; v <= n; v++) {
        s.insert(find(v));
    }

    cout << sz(s);

    return 0;
}