#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Angle {
	int x, y, idx;
	int t;
	Angle(int x, int y, int idx, int t=0) : x(x), y(y), idx(idx), t(t) {}
	Angle operator-(Angle b) const { return {x-b.x, y-b.y, t}; }
	int half() const {
		assert(x || y);
		return y < 0 || (y == 0 && x < 0);
	}
	Angle t90() const { return {-y, x, t + (half() && x >= 0)}; }
	Angle t180() const { return {-x, -y, t + half()}; }
	Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b) {
	// add a.dist2() and b.dist2() to also compare distances
	return make_tuple(a.t, a.half(), a.y * (ll)b.x) <
	       make_tuple(b.t, b.half(), a.x * (ll)b.y);
}
bool operator==(Angle a, Angle b) {
	// add a.dist2() and b.dist2() to also compare distances
	return make_tuple(a.t, a.half(), a.y * (ll)b.x) ==
	       make_tuple(b.t, b.half(), a.x * (ll)b.y);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    vector<Angle> a;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back(Angle{x, y, i});
    }

    sort(all(a));

    vector<int> cnt(1, 1);
    vector<int> idx_to_loc(n);

    idx_to_loc[a[0].idx] = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (a[i] == a[i + 1]) cnt.back()++;
        else cnt.push_back(1);
        idx_to_loc[a[i + 1].idx] = sz(cnt) - 1;
    }

    const int m = sz(cnt);
    vector<int> psum(m << 1);
    for (int i = 0; i < m; i++) cnt.push_back(cnt[i]);
    for (int i = 0; i < 2 * m; i++) psum[i] = cnt[i] + (i > 0 ? psum[i - 1] : 0);

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        l = idx_to_loc[l];
        r = idx_to_loc[r];
        swap(l, r);
        if (l > r) r += m;
        
        int ans = psum[r] - (l > 0 ? psum[l - 1] : 0);
        cout << ans << '\n';
    }

    return 0;
}
