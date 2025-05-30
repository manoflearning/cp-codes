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

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
    cin >> n >> m;
    vector<string> a(n);
    set<string> st;
    for (auto& i : a) cin >> i;
    for (int i = 0; i < m; i++) {
        string x; cin >> x;
        st.insert(x);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        string res;
        res.push_back(a[i][3]);
        res.push_back(a[i][3 + 1]);
        res.push_back(a[i][3 + 2]);
        //cout << res << '\n';
        if (st.count(res)) ans++;
    }

    cout << ans;

	return 0;
}