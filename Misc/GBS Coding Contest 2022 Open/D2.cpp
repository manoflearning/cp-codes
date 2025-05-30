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

ll x;

void f(ll x) {
    if (x == 0) return;

    ll lb = sqrt(x);

    for (int i = 0; i < lb; i++) cout << 'A';
    for (int i = 1; i < 25; i++) cout << (char)('A' + i);
    for (int i = 0; i < lb; i++) cout << 'Z';

    f(x - lb * lb);
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> x;

    if (x == 0) {
        cout << "MANOFLEARNING";
        return 0;
    }

    f(x);

	return 0;
}