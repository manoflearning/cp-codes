#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

// struct Tree {
// 	typedef int T;
// 	static constexpr T unit = INT_MIN;
// 	T f(T a, T b) { return max(a, b); } // (any associative fn)
// 	vector<T> s; int n;
// 	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
// 	void update(int pos, T val) {
// 		for (s[pos += n] = val; pos /= 2;)
// 			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
// 	}
// 	T query(int b, int e) { // query [b, e)
// 		T ra = unit, rb = unit;
// 		for (b += n, e += n; b < e; b /= 2, e /= 2) {
// 			if (b % 2) ra = f(ra, s[b++]);
// 			if (e % 2) rb = f(s[--e], rb);
// 		}
// 		return f(ra, rb);
// 	}
// };

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        int sum{};
        vector<vector<int>> a(n, vector<int>(m));
        for (auto &i : a) for (auto &j : i) {
            cin >> j;
            sum += j;
        }

        const int target = sum / 2;

        vector<int> ans(n, 0);
        int cnt_d{0};
        for (int i = n - 1; i >= 0; i--) {
            int &j = ans[i];
            while (j < m && cnt_d < target) {
                cnt_d += a[i][j];
                j++;
            }
            if (cnt_d == target) break;
        }

        assert(cnt_d == target);

        cout << (ll)cnt_d * (sum - cnt_d) << '\n';
        string s;
        for (int i = 0; i <= n; i++) {
            int diff = (i == 0 ? ans[0] : (i == n ? m - ans[i - 1] : ans[i] - ans[i - 1]));
            while (diff--) s.push_back('R');
            if (i < n) s.push_back('D');
        }
        cout << s << '\n';
    }

    return 0;
}

