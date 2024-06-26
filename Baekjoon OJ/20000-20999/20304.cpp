#include <bits/stdc++.h>
using namespace std;

int n, dist[1010101];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    memset(dist, -1, sizeof(dist));

    cin >> n;
    queue<int> q;
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        q.push(x);
        dist[x] = 0;
    }

    int ans = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        ans = max(ans, dist[v]);

        for (int i = 1; i <= n; i <<= 1) {
            int u = -1;
            if (v & i) u = v - i;
            else u = v + i;
            if (u > n) continue;
            if (dist[u] == -1) {
                q.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    }

    cout << ans;
}