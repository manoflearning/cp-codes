#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// struct Tree {
// 	typedef pair<ll, int> T;
// 	// static constexpr T unit = {0, 0};
// 	T f(T a, T b) {
//         T ret{};
//         ret.first = a.first + b.first;
//         ret.second = a.second + b.second;
//         return ret;
//     } // (any associative fn)
// 	vector<T> s; int n;
// 	Tree(int n = 0, T def = {0, 0}) : s(2*n, def), n(n) {}
// 	void update(int pos, T val) {
//         pos += n;
// 		for (s[pos] = f(s[pos], val); pos /= 2;)
// 			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
// 	}
// 	T query(int b, int e) { // query [b, e)
// 		T ra = {0, 0}, rb = {0, 0};
// 		for (b += n, e += n; b < e; b /= 2, e /= 2) {
// 			if (b % 2) ra = f(ra, s[b++]);
// 			if (e % 2) rb = f(s[--e], rb);
// 		}
// 		return f(ra, rb);
// 	}
// };

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
    void assign(int n) {
        s.assign(n, 0);
    }
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    map<int, int> mp;
    vector<vector<int>> c(n, vector<int>(m));
    for (auto &i : c) for (auto &j : i) {
        cin >> j;
        mp[j]++;
    }

    for (auto &i : c) for (auto &j : i) {
        if (mp[j] == 1) j = 0;
    }

    vector<int> cc;
    for (auto &i : c) for (auto &j : i) {
        if (j) cc.push_back(j);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (auto &i : c) for (auto &j : i) {
        if (j) j = lower_bound(all(cc), j) - cc.begin() + 1;
    }

    ll ans = 0;

    vector<FT> fw_sum(sz(cc) + 1, FT(n));
    vector<FT> fw_cnt(sz(cc) + 1, FT(n));

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (!c[i][j]) continue;

            auto sum = fw_sum[c[i][j]].query(i + 1);
            auto cnt = fw_cnt[c[i][j]].query(i + 1);
            ans += cnt * (i + j) + sum;

            fw_sum[c[i][j]].update(i, -i - j);
            fw_cnt[c[i][j]].update(i, 1);
        }
    }

    for (auto &i : fw_sum) i.assign(n);
    for (auto &i : fw_cnt) i.assign(n);

    for (int j = m - 1; j >= 0; j--) {
        for (int i = n - 1; i >= 0; i--) {
            if (!c[i][j]) continue;
            
            auto sum = fw_sum[c[i][j]].query(i);
            auto cnt = fw_cnt[c[i][j]].query(i);
            ans += cnt * (i - j) + sum;

            fw_sum[c[i][j]].update(i, -i + j);
            fw_cnt[c[i][j]].update(i, 1);
        }
    }

    cout << ans << '\n';
}