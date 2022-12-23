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

string ans[31];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    ans[0] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 1; i <= 30; i++) {
        int l = (1 << (i / 2)), r = (1 << (i / 2));
        if (i & 1) l *= 2;
        for (int j = 0; j < l; j++) ans[i].push_back('A');
        for (int j = 1; j < 25; j++) ans[i].push_back(j + 'A');
        for (int j = 0; j < r; j++) ans[i].push_back('Z');
    }

    ll x; cin >> x;

    if (x == 0) {
        cout << "MANOFLEARNING";
        return 0;
    }

    for (int i = 0; i <= 30; i++) {
        cout << i << ' ' << sz(ans[i]) << '\n';
    }

    for (int i = 0; i <= 30; i++) {
        if ((1 << i) & x) {
            cout << ans[i];
        }
    }

	return 0;
}