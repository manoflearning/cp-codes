//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXV = 101;

int x, n;
ll ub;
ll adj[MAXV][MAXV], w[MAXV], minw = INF;
ll a[101010], psum[101010], arr[101010] = { 1, };

void init() {
	for (int i = 0; i < MAXV; i++) {
		for (int j = 0; j < MAXV; j++) {
			adj[i][j] = INF;
		}
	}
}

void input() {
    cin >> x >> n >> ub;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj[i][j];
        }
    }

    for (int v = 1; v <= n; v++) {
        cin >> w[v];
        minw = min(minw, w[v]);
    }
}

void floyd() {
	for (int k = 1; k <= n; k++) {
		for (int u = 1; u <= n; u++) {
			for (int v = 1; v <= n; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

	input();

    floyd();
    
    for (int i = 1; i <= x; i++) {
        cin >> arr[i];
        a[i] = adj[arr[i - 1]][arr[i]];
        psum[i] = a[i] + psum[i - 1];
    }

    if (psum[x] + minw <= ub) {
        cout << 0 << ' ' << psum[x] + minw;
        return 0;
    }

    ll ans1 = INF, ans2 = INF;
    for (int st = 1; st < x; st++) {
        if (psum[st] + w[arr[st]] <= ub && (x - st < ans1 || (x - st == ans1 && psum[st] + w[arr[st]] < ans2))) {
            ans1 = x - st;
            ans2 = psum[st] + w[arr[st]];
        }

        ll res = psum[st] + w[arr[st]], res2 = -1;
        int l = st + 1, r = x;
        while (l < r) {
            int mid = (l + r) >> 1;
            res2 = psum[x] - psum[mid] + adj[arr[st]][arr[mid]];
            if (res + res2 <= ub) r = mid;
            else l = mid + 1;
        }

        if (res + res2 > ub) continue;

        if (l - st - 1 < ans1 || (l - st - 1 == ans1 && res + res2 < ans2)) {
            ans1 = l - st - 1;
            ans2 = res + res2;
        }
    }

    if (ans1 == INF) {
        cout << -1;
        return 0;
    }

    cout << ans1 << ' ' << ans2;

	return 0;
}