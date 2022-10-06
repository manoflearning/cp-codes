#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> p(505050, -1);

int find(int v) {
    if (p[v] < 0) return v;
    return p[v] = find(p[v]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    p[V] += p[U];
    p[U] = V;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (find(u) == find(v)) { ans = i + 1; break; }
        merge(u, v);
    }

    cout << ans;

    return 0;
}