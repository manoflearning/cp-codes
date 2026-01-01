#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 101010;
constexpr int M = 101010;

int n, m;
struct node {
    vector<int> a;
    int idx;
};
vector<node> a;

set<int> st[M];
vector<int> mex(M);

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        a[i].a.resize(m);
        a[i].idx = i + 1;
        for (auto &j : a[i].a) cin >> j;
    }

    sort(all(a), [&](const node &i, const node &j) {
        return sz(i.a) < sz(j.a);
    });

    ll c = 0;
    for (auto &i : a) {
        c += sz(i.a);
    }

    ll lo = c / n, hi = (c + n - 1) / n;

    int l = -1, r = n;
    for (int i = 0; i < n; i++) {
        if (sz(a[i].a) < lo) l = i;
        if (r == n && hi < sz(a[i].a)) r = i;
    }

    for (int i = 0; i <= l; i++) {
        for (auto &x : a[i].a) st[x].insert(i);
    }

    vector<tuple<int, int, int>> ans;
    for (int i = r; i < n; i++) {
        int rem = sz(a[i].a) - hi;
        for (auto &x : a[i].a) {
            if (!rem) break;

            while (mex[x] <= l && (st[x].count(mex[x]) || sz(a[mex[x]].a) == lo)) mex[x]++;
            if (l < mex[x]) continue;

            ans.push_back({a[i].idx, a[mex[x]].idx, x});

            rem--;

            st[x].insert(mex[x]);
            a[mex[x]].a.push_back(x);
        }
    }

    cout << sz(ans) << '\n';
    for (auto &[x, y, z] : ans) {
        cout << x << ' ' << y << ' ' << z << '\n';
    }
}