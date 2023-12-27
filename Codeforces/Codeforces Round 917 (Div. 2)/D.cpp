// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 202020, MAXK = 202020;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
        t.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		// for (int i = flag; i < flag + n; i++) cin >> t[i];
		// for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg, seg2;

int n, k;
ll p[MAXN], q[MAXK];
ll pow2[22];

void init() {}

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i <= k; i++) {
        cin >> q[i];
        q[i]++;
    }
}

// ll case1() {
//     ll ret = 0;

//     seg.build(2 * n - 1);
//     for (int i = 1; i <= n; i++) {
//         ret = (ret + seg.query(p[i] + 1, 2 * n - 1)) % MOD;
//         seg.modify(p[i], 1);
//     }
//     ret = (ret * k) % MOD;
    
//     return ret;
// }

ll solve1() {
    ll ret = 0;

    seg.build(k);
    for (int i = 1; i <= n; i++) {
        ret = (ret + seg.query(q[i] + 1, k)) % MOD;
        seg.modify(q[i], 1);
    }
    ret = (ret * n) % MOD;
    
    return ret;
}

ll solve2() {
    ll ret = 0;

    map<int, ll> diffCnt;

    for (int x = 1; x <= 2 * n - 1; x += 2) {
        for (int diff = -20; diff < 0; diff++) {
            ll ub = pow2[-diff] * x;
            ub = min<ll>(ub, 2 * n);
            // [1, ub) 범위의 원소의 수 만큼 pair 만들 수 있다
            diffCnt[diff] = (diffCnt[diff] + ub / 20) % MOD;
        }
        for (int diff = 1; diff <= 20; diff++) {
            ll lb = pow2[diff] * x;
            lb = min<ll>(lb, 2 * n);
            // (lb, 2n - 1] 범위의 원소의 수 만큼 pair 만들 수 있다
            diffCnt[diff] = (diffCnt[diff] + (2 * n - lb) / 2) % MOD;
        }
    }

    seg2.build(2 * n - 1);
    for (int i = 1; i <= k; i++) {
        for (int j = -20; j <= 20; j++) {
            if (q[i] - j < 1 || k < q[i] - j) continue;
            ll val = seg.query(q[i] - j, q[i] - j);
            if (val == 0) continue;

            ret = (ret + diffCnt[j]) % MOD;
        }
        
        ret = (ret + seg.query(1, q[i] + 21) * n % MOD * n % MOD) % MOD;
    }

    return ret;
}

// ll case2() { // abs(q[i] - q[j]) <= 20
//     ll ret = 0;

//     map<int, ll> diffCnt;
//     seg.build(k);
//     for (int i = 1; i <= k; i++) {
//         for (int j = -20; j <= 20; j++) {
//             if (q[i] - j < 1 || k < q[i] - j) continue;
//             ll val = seg.query(q[i] - j, q[i] - j);
//             if (val > 0) diffCnt[j] = (diffCnt[j] + val) % MOD;
//         }
//         seg.modify(q[i], 1);
//     }
    
//     // 모든 (x, y) pair 개수 세기
//     for (auto& it : diffCnt) {
//         auto [diff, cnt] = it;
        
//         ll res = 0;
        
//         if (diff < 0) { // if diff < 0, q[i] > q[j]
//             for (int x = 1; x <= 2 * n - 1; x += 2) {
//                 ll ub = pow2[-diff] * x;
//                 ub = min<ll>(ub, 2 * n);
//                 // [1, ub) 범위의 원소의 수 만큼 pair 만들 수 있다
//                 res = (res + ub / 2) % MOD;
//             }
//         }
//         else { // if diff > 0, q[i] < q[j]
//             for (int y = 1; y <= 2 * n - 1; y += 2) {
//                 ll lb = pow2[diff] * y;
//                 lb = min<ll>(lb, 2 * n);
//                 // (lb, 2n - 1] 범위의 원소의 수 만큼 pair 만들 수 있다
//                 res = (res + (2 * n - lb) / 2) % MOD;
//             }
//         }

//         res = (res * cnt) % MOD;
//         ret = (ret + res) % MOD;
//     }
    
//     return ret;
// }

// ll case3() { // abs(q[i] - q[j]) > 20
//     ll ret = 0;

//     seg.build(k);
//     for (int i = 1; i <= k; i++) {
//         ret = (ret + seg.query(q[i] + 21, k) * n % MOD * n % MOD) % MOD;
//         seg.modify(q[i], 1);
//     }

//     return ret;
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    pow2[0] = 1;
    for (int i = 1; i <= 20; i++)
        pow2[i] = 2 * pow2[i - 1];

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        ll ans = 0;
        ans = (ans + solve1()) % MOD;
        ans = (ans + solve2()) % MOD;
        // ans = (ans + case3()) % MOD;

        cout << ans << '\n';
    }
}