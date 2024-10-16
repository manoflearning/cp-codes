#include <bits/stdc++.h>
using namespace std;

const int MAX = 303030;

vector<int> p(MAX, -1);

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    p[U] = V;
}

int n;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n - 2; i++) {
        int u, v;
        cin >> u >> v;
        merge(u, v);
    }

    for (int i = 2; i <= n; i++) {
        if (find(1) != find(i)) {
            cout << 1 << ' ' << i;
            return 0;
        }
    }

    return 0;
}