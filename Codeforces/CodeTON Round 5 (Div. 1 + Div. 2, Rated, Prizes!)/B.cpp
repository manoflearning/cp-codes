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

void getbit(int& bit, const vector<int>& a, int x) {
    for (auto& i : a) {
        int nbit = bit | i;
        if (nbit - (nbit & x)) break;
        bit = nbit;
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
        int n, x;
        cin >> n >> x;
        vector<int> a(n), b(n), c(n);
        for (auto& i : a) cin >> i;
        for (auto& i : b) cin >> i;
        for (auto& i : c) cin >> i;

        int b1 = 0, b2 = 0, b3 = 0;
        getbit(b1, a, x);
        getbit(b2, b, x);
        getbit(b3, c, x);

        if ((b1 | b2 | b3) == x) cout << "Yes\n";
        else cout << "No\n";
	}
}