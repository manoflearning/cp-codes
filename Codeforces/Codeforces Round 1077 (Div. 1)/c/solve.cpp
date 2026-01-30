#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

struct Tree {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] += val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

struct Edge {
    int u, v;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<Edge> e(m);
        vector<vector<int>> v_to_u(n), u_to_v(n);
        for (auto &i : e) {
            cin >> i.u >> i.v;
            i.u--, i.v--;
            v_to_u[i.v].push_back(i.u);
            u_to_v[i.u].push_back(i.v);
        }

        

        // // sort(all(e), [&](const Edge &i, const Edge &j) {
        // //     return i.v > j.v;
        // // });

        // vector<int> dist(n + 1, INF);
        // dist[n] = -1;
        // for (int v = n - 1; v >= 0; v--) {
        //     dist[v] = min(dist[v], dist[v + 1] + 1);
            
        //     for (const int u : v_to_u[v]) {
        //         dist[u] = min(dist[u], dist[v] + 1);
        //     }
        // }

        // ll ans = 0;

        // { // case 1
        //     Tree seg{n + 5}, sum{n + 5};
        //     int ui = -1, vi = -1;
        //     for (int y = 0; y < n; y++) {
        //         if (y < vi) {
        //             // const ll cnt1 = seg.query(0, dist[y]);
        //             const ll cnt2 = seg.query(dist[y], n);
        //             if (cnt2) cout << cnt2 << ' ' << y << '\n';
        //             // ans += cnt1 * dist[y];
        //             ans += cnt2 * (dist[y] - dist[vi]);
        //         }

        //         seg.update(dist[y], 1);
        //         sum.update(dist[y], dist[y]);
        //         for (const int v : u_to_v[y]) {
        //             if (vi < v) {
        //                 ui = y, vi = v;
        //             }
        //         }
        //     }
        // }
        // { // case 2
        //     // Tree seg{n + 5}, seg_dist{n + 5};
        //     // int vi = -1;
        //     // for (int x = 0; x < n; x++) {
        //     //     if (x < vi) {
        //     //         ans += seg_dist.query(0, dist[x] + 1) - seg.query(0, dist[x] + 1) * dist[vi];
        //     //     }

        //     //     seg.update(dist[x], 1);
        //     //     seg_dist.update(dist[x], dist[x]);
        //     //     for (const int v : u_to_v[x]) vi = max(vi, v);
        //     // }
        // }

        cout << ans << '\n';
    }
}

// 1. if x < y:
// - 1.1. if there exists (ui, vi) s.t. ui < y < vi
//   - dist[x] >= dist[y]이면서 x <= ui를 만족하는 x에 대해서, x <= ui를 만족하는 가장 큰 vi를 찾아 ans += dist[y] - dist[vi]
// - 1.2. otherwise => f(x, y) = 0








// 1. if x < y:
// 1.1. if there exists (ui, vi) s.t. ui < y < vi
// 1.1.1. if dist(x, vi) < dist(y, vi) => f(x, y) = 0
// 1.1.2. if dist(x, vi) >= dist(y, vi) => f(x, y) = dist(y, vi)
// 1.2. otherwise => f(x, y) = 0

// 2. if y < x:
// 2.1. if there exists (ui, vi) s.t. ui < x < vi
// 2.1.1. if dist(y, vi) > dist(x, vi) => f(x, y) = 0
// 2.1.2. if dist(y, vi) <= dist(x, vi) => f(x, y) = dist(y, vi)
// 2.2. otherwise => f(x, y) = 0

// 1. if x < y:
// 1.1. if there exists (ui, vi) s.t. ui < y < vi
// 1.1.1. if dist(x, vi) < dist(y, vi) => f(x, y) = dist(y, n)
// 1.1.2. if dist(x, vi) >= dist(y, vi) => f(x, y) = dist(y, vi)
// 1.2. otherwise => f(x, y) = 0

// 2. if y < x:
// 2.1. if there exists (ui, vi) s.t. ui < x < vi
// 2.1.1. if dist(y, vi) > dist(x, vi) => f(x, y) = dist(y, n)
// 2.1.2. if dist(y, vi) <= dist(x, vi) => f(x, y) = dist(y, vi)
// 2.2. otherwise => f(x, y) = dist(y, n)