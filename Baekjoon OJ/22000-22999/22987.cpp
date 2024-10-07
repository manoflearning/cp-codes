#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 505050;
const int INF = 1e9 + 7;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
		// for (int i = flag; i < flag + n; i++) cin >> t[i];
		// for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n, nl, nr);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
	void propagate(int n, int nl, int nr) {
		if (lazy[n] != 0) {
			if (n < flag) {
				lazy[n << 1] += lazy[n];
				lazy[n << 1 | 1] += lazy[n];
			}
			t[n] += lazy[n] * (nr - nl + 1);
			lazy[n] = 0;
		}
	}
}seg;

int n;
ll x[MAXN], h[MAXN];
struct Node {
    ll s1, e1;
    ll s2, e2;
};
Node a[MAXN];

vector<ll> cc;
void coor_comp() {
    cc.push_back(-LLONG_MIN);
    for (int i = 1; i <= n; i++) {
        cc.push_back(a[i].s1);
        cc.push_back(a[i].e1);
        cc.push_back(a[i].s2);
        cc.push_back(a[i].e2);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (int i = 1; i <= n; i++) {
        a[i].s1 = lower_bound(all(cc), a[i].s1) - cc.begin();
        a[i].e1 = lower_bound(all(cc), a[i].e1) - cc.begin();
        a[i].s2 = lower_bound(all(cc), a[i].s2) - cc.begin();
        a[i].e2 = lower_bound(all(cc), a[i].e2) - cc.begin();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> h[i];
        a[i].s1 = x[i] - h[i];
        a[i].e1 = x[i] + h[i];
        a[i].s2 = x[i] - 3 * h[i];
        a[i].e2 = x[i] + 3 * h[i];
    }

    coor_comp();
    
    vector<int> ord(n);
    iota(all(ord), 1);
    sort(all(ord), [&](int p1, int p2) {
        return h[p1] > h[p2];
    });

    vector<int> ans;
    seg.build(sz(cc));
    for (auto& i : ord) {
        if (seg.query(a[i].s1, a[i].e1) > 0) continue;
        ans.push_back(i);
        seg.modify(a[i].s1, a[i].e1, 1);
    }

    cout << sz(ans) << '\n';
    sort(all(ans));
    for (auto& i : ans)
        cout << i << ' ';
}


// [Xi, Xi + 2Hi]
// [Xi, Xi + 6Hi]
// 간섭이 일어날 수 있는 기지국 쌍 (u, v)를 엣지로 연결
// 구간 그래프?
// #include <bits/stdc++.h>
// using namespace std;
// #define ll long long
// #define fr first
// #define sc second
// #define sz(x) (int)(x).size()
// #define all(x) (x).begin(), (x).end()

// const int MAXN = 505050;
// const int INF = 1e9 + 7;

// int n;
// struct Node {
//     ll s1, e1;
//     ll s2, e2;
//     int idx;
//     bool operator<(const Node& rhs) const {
//         return s1 < rhs.s1;
//     }
// };
// Node a[MAXN];

// int smin[MAXN << 2];
// vector<int> s1idx[MAXN << 2];

// void input() {
//     cin >> n;
//     for (int i = 1; i <= n; i++) {
//         ll x, h;
//         cin >> x >> h;
//         a[i].s1 = x - h;
//         a[i].e1 = x + h;
//         a[i].s2 = x - 3 * h;
//         a[i].e2 = x + 3 * h;
//         a[i].idx = i;
//     }
// }

// vector<ll> cc;
// void coor_comp() {
//     cc.push_back(-LLONG_MIN);
//     for (int i = 1; i <= n; i++) {
//         cc.push_back(a[i].s1);
//         cc.push_back(a[i].e1);
//         cc.push_back(a[i].s2);
//         cc.push_back(a[i].e2);
//     }

//     sort(all(cc));
//     cc.erase(unique(all(cc)), cc.end());

//     for (int i = 1; i <= n; i++) {
//         a[i].s1 = lower_bound(all(cc), a[i].s1) - cc.begin();
//         a[i].e1 = lower_bound(all(cc), a[i].e1) - cc.begin();
//         a[i].s2 = lower_bound(all(cc), a[i].s2) - cc.begin();
//         a[i].e2 = lower_bound(all(cc), a[i].e2) - cc.begin();
//     }
// }

// int dp[MAXN << 2];
// int opt[MAXN << 2];
// int opt2[MAXN << 2];
// int opt3[MAXN << 2];

// void bottomup() {
//     for (int i = sz(cc) - 1; i >= 1; i--) {
//         if (smin[i] == INF) {
//             opt[i] = -1;
//             opt2[i] = -1;
//             opt3[i] = INF;
//             dp[i] = 0;
//             continue;
//         }

//         int lb = max(i, smin[i]);

//         for (auto& j : s1idx[i]) {
//             if (lb < a[j].s2) continue;
//             if (dp[a[j].e1 + 1] == INF) continue;
//             if (opt3[i] <= a[j].s2) continue;
//             opt[i] = j;
//             opt2[i] = a[j].e1 + 1;
//             opt3[i] = a[j].s2;
//             dp[i] = 1 + dp[a[j].e1 + 1];
//         }

//         if (0 < dp[i + 1] && dp[i + 1] != INF && a[opt[i + 1]].s2 <= lb && opt3[i] > opt3[i + 1]) {
//             opt[i] = opt[i + 1];
//             opt2[i] = opt2[i + 1];
//             opt3[i] = opt3[i + 1];
//             dp[i] = dp[i + 1];
//         }
//     }

//     assert(dp[1] > 0);

//     cout << dp[1] << '\n';
//     int x = 1;
//     while (x > 0 && opt[x] > 0 && opt2[x] > 0) {
//         cout << opt[x] << ' ';
//         assert(opt2[x] > 0);
//         x = opt2[x];
//     }
// }

// int main() {
//     #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     #endif

//     cin.tie(NULL); cout.tie(NULL);
//     ios_base::sync_with_stdio(false);

//     input();

//     coor_comp();

//     for (int i = 0; i < (MAXN << 2); i++) {
//         smin[i] = dp[i] = INF;
//     }
//     for (int i = 1; i <= n; i++) {
//         smin[a[i].e1] = min<int>(smin[a[i].e1], a[i].s1);
//         s1idx[a[i].s1].push_back(i);
//     }
//     for (int i = sz(cc) - 2; i >= 0; i--) {
//         smin[i] = min(smin[i], smin[i + 1]);
//     }
//     for (int i = 0; i < (MAXN << 2); i++) {
//         opt[i] = opt2[i] = -1;
//         opt3[i] = INF;
//     }

//     bottomup();
// }
