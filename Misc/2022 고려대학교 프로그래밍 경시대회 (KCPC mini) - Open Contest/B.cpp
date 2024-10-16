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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll n, k;
struct Node {
    ll x, t, s;
};
vector<Node> a;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k;
    a.resize(k);
    for (auto& i : a) {
        cin >> i.x >> i.t >> i.s;
    }
    sort(all(a), [](Node lhs, Node rhs) {
        return lhs.x < rhs.x;
    });

    ll ans = 0, prv = 0;
    for (auto& i : a) {
        ans += i.x - prv;
        prv = i.x;
        if (ans < i.s) ans = i.s;
        ll diff = ans - i.s;
        if ((diff / i.t) & 1) 
            ans += i.t - (diff % i.t);
    }
    ans += n - prv;

    cout << ans;

	return 0;
}