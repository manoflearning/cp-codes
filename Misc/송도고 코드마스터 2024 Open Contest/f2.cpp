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

struct Fenwick { // 0-indexed
	int flag, cnt; // array size
	vector<ll> arr, t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1, cnt++);
		arr.resize(flag);
		t.resize(flag);
	}
	void add(int p, ll value) { // add value at position p
        value %= MOD;
        value = (value + MOD) % MOD;

		arr[p] = (arr[p] + value) % MOD;
		while (p < flag) {
			t[p] = (t[p] + value) % MOD;
			p |= p + 1;
		}
	}
	void modify(int p, ll value) { // set value at position p
		add(p, value - arr[p]);
	};
	ll query(int x) {
		ll ret = 0;
		while (x >= 0) ret = (ret + t[x]) % MOD, x = (x & (x + 1)) - 1;
		return ret;
	}
	ll query(int l, int r) {
		return (query(r) - (l ? query(l - 1) : 0) + MOD) % MOD;
	}
}fw0, fw1;

int n, k;
vector<int> a;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    fw0.build(2 * n + 5);
    fw1.build(2 * n + 5);
    
    // base case: [n + 1, n + 1]
    fw0.modify(n + 1, 1);

    // inductive step: [n + 1 - i, n + 1]
    for (int i = 1; i <= n; i++) {
        // previous
        int st = n + 1 - i;
        if (a[i] == 0) {
            fw0.add(st, fw0.query(st + 1, st + k));
            fw1.add(st, fw0.query(st + k + 1, st + k + 1));
            fw1.add(st, fw1.query(st + 1, st + k + 1));
        }
        // now
        {
            ll tmp = fw0.query(st + k, st + k);
            fw0.modify(st + k, 0);
            fw1.add(st + k, tmp);
        }
        {
            fw0.modify(st + k + 1, 0);
            fw1.modify(st + k + 1, 0);
        }
    }

    cout << fw1.query(1, 1 + k + 1);
}
