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

int n, dep[101010], en;
vector<int> t[101010];

void dfs(int v) {
    if (t[v][0] != -1) {
        dep[t[v][0]] = dep[v] + 1;
        dfs(t[v][0]);
    }
    en = v;
    if (t[v][1] != -1) {
        dep[t[v][1]] = dep[v] + 1;
        dfs(t[v][1]);
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        t[a].push_back(b);
        t[a].push_back(c);
    }

    dfs(1);
    
    cout << 2 * (n - 1) - dep[en];

	return 0;
}