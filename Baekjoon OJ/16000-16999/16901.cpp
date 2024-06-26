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

const int MAXD = 31; 

struct Node {
    int child[2];
};

int n;
vt<ll> a;
vt<Node> trie(1, { -1, -1 });

void input() {
    cin >> n;
    a.resize(n);
    EACH(i, a) cin >> i;
    sort(all(a));
    a.erase(unique(all(a)), a.end());
}

void insert(int bit, int x = 0, int key = MAXD) {
    auto& now = trie[x];
    if (key == 0) return;
        
    int next = (bit & (1 << (key - 1)) ? 1 : 0);

    if (now.child[next] == -1) { 
        now.child[next] = sz(trie);
        trie.push_back({ -1, -1 });
    }

    insert(bit, now.child[next], key - 1);
}

ll query(ll x, int bit, int bit2, int key) {
    auto& now = trie[x];
    if (key == 0) return bit;
    else {
        int next = (x & (1 << (key - 1)) ? 1 : 0);
        if (now.child[next]) return query(x, bit, bit2, key - 1);
        else return query(x, bit, bit2 | (1 << (key - 1)), key - 1);
    }
}

ll solve(int x, int xl, int xr, int prv, int key = MAXD) {
    if (key == 0) return 0;

    ll ret = 0;
    auto& now = trie[x];
    int mid = lower_bound(a.begin() + xl, a.begin() + xr + 1, prv + (1 << (key - 1))) - a.begin() - 1;

    if (now.child[0] != -1) ret += solve(now.child[0], xl, mid, prv, key - 1);
    if (now.child[1] != -1) ret += solve(now.child[1], mid + 1, xr, prv + (1 << (key - 1)), key - 1);

    if (now.child[0] == -1 || now.child[1] == -1) return ret;
    
    ll res = 1e18;
    FOR(i, mid + 1, xr + 1) {
        res = min(res, query(now.child[0], a[i] - prv - (1 << (key - 1)), 0, key - 1));
    }
    ret += res;
    
    return ret;
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

	input();

    EACH(i, a) insert(i);

    cout << solve(0, 0, sz(a) - 1, 0);

	return 0;
}