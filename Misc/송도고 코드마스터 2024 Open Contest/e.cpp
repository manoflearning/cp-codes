// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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

int gn[101010];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    gn[1] = 0;
    for (int i = 2; i < 101010; i++)
        gn[i] = i - 1;
    
	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
        int r, c;
        cin >> r >> c;

        bool jinseo_win = (gn[r] ^ gn[c] ? 1 : 0);

        if (jinseo_win) {
            cout << "jinseo\n";
            cout << min(r, c) << ' ' << min(r, c) << '\n';
        }
        else cout << "dohoon\n";
	}
}
