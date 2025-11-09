#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 202020;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, int val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg;

int n, p[N], rp[N];
int pad = 0;
vector<int> ans;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = n; i >= 1; i--) {
        cin >> p[i];
        rp[p[i]] = i;
    }

    seg.build(n);

    for (int x = n; x >= 1; x--) {
        int idx = rp[x] - seg.query(1, rp[x] - 1);

        // cout << "initial idx = " << idx << ", pad = " << pad << '\n';
        idx = idx - pad;
        if (idx < 1) idx += x;
        // cout << "modified idx = " << idx << '\n';

        pad = (pad + idx - 1) % x;

        seg.add(rp[x], 1);

        ans.push_back(idx);
    }

    reverse(all(ans));

    for (auto &i : ans)
        cout << i << ' ';
}