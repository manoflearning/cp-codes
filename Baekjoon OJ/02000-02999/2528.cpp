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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct lend {
    ll len, d;
};

ll n, mx;
vector<lend> a;

int cald(int idx, ll t, int& l, int& r) {
    ll m = (mx - a[idx].len);

    t %= (m << 1);

    if (t < m) {
        ll dist = t;
        if (!a[idx].d) l = dist, r = l + a[idx].len;
        else r = mx - dist, l = r - a[idx].len;
        return a[idx].d;
    }
    else {
        ll dist = m - t;
        if (!a[idx].d) l = dist, r = l + a[idx].len;
        else r = mx - dist, l = r - a[idx].len;
        return !a[idx].d;
    }
}

ll cal(int now, ll t) {
    if (now == n) return t;

    if (a[now].len + a[now + 1].len >= mx) return cal(now + 1, t);
    
    int l1 = -1, r1 = -1;
    int l2 = -1, r2 = -1;
    int d1 = cald(now, t, l1, r1), d2 = cald(now + 1, t, l2, r2);

    if (l1 > l2) { // wlog
        swap(l1, l2);
        swap(r1, r2);
        swap(d1, d2);
    }

    if (l2 <= r1) return cal(now + 1, t);

    if (d1 == d2) return cal(now + 1, t + (mx - r2) + (l2 - r1) / 2);
    else return cal(now + 1, t + (l2 - r1) / 2);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> mx;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i].len >> a[i].d;

    cout << cal(1, 0);

	return 0;
}