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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll A, B, C, K;
int dp[1010101][4];

int f(int v, int d) {
    int& ret = dp[v][d];
    if (ret != -1) return ret;
    if (v == 0) return ret = (d == 0 ? 0 : INF); 

    ret = INF;
    if (v >= A) ret = min(ret, 1 + f(v - A, (d + 3) % 4));
    if (v >= B) ret = min(ret, 1 + f(v - B, (d + 1) % 4));
    if (v >= C) ret = min(ret, 1 + f(v - C, (d + 2) % 4));
    
    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> A >> B >> C >> K;

    for (int i = 0; i < 1010101; i++) {
        dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = -1;
    }

    cout << (f(K, 0) < INF ? f(K, 0) : -1);

	return 0;
}