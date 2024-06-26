#define _USE_MATH_DEFINES
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

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Ans {
    string s; int l, r;
};

ll n, k;
vt<Ans> ans;

vt<int> sw(int l, int r, vt<int> a) {
    swap(a[l], a[r]);
    return a;
}

vt<int> rv(int l, int r, vt<int> a) {
    for (int i = l; i <= (l + r) / 2; i++) {
        swap(a[i], a[r - i + l]);
    }
    return a;
}

int f(vt<int> a, int idx) {
    if (idx == 5) {
        int ret = 1;
        FOR(i, 1, n + 1) ret &= (i == a[i]);
        return ret;
    }
    
    FOR(l, 1, n + 1) {
        FOR(r, l + 1, n + 1) {
            if (f(sw(l, r, a), idx + 1)) {
                ans.push_back({ "swap", l, r });
                return 1;
            }
            if (f(rv(l, r, a), idx + 1)) {
                ans.push_back({ "reverse", l, r });
                return 1;
            }
        }
    }
    return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k;

    if (n < 5) {
        vt<int> a(1, 0);
        FOR(k) a.push_back(n - k + i + 1);
        FOR(n - k) a.push_back(i + 1);
        if (f(a, 0)) {
            cout << "YES\n";
            FOR(i, 4, -1, -1) cout << ans[i].s << ' ' << ans[i].l << ' ' << ans[i].r << '\n';
        }
        else cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    int cnt = 0;

    if (k == 1) {
        cout << "swap " << k + 1 << ' ' << n << '\n';
        cout << "swap " << k + 1 << ' ' << n << '\n';
        cout << "swap " << k + 1 << ' ' << n << '\n';
        cout << "reverse " << k + 2 << ' ' << n - 1 << '\n';
        cout << "reverse 1 " << n << '\n';
    }
    else if (n - k == 1) {
        cout << "swap " << 1 << ' ' << k << '\n';
        cout << "swap " << 1 << ' ' << k << '\n';
        cout << "swap " << 1 << ' ' << k << '\n';
        cout << "reverse " << 2 << ' ' << k - 1 << '\n';
        cout << "reverse 1 " << n << '\n';
    }
    else {
        cout << "reverse 1 " << k << '\n';
        cout << "reverse 1 " << k << '\n';
        cout << "reverse 1 " << k << '\n';
        cout << "reverse " << k + 1 << ' ' << n << '\n';
        cout << "reverse 1 " << n << '\n';
    }
    
	return 0;
}