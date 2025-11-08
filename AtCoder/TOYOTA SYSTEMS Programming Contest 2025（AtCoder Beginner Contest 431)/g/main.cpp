#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int MOD = 1e9 + 7;

constexpr int N = 202020;
constexpr int Q = 202020;

int flag;    // array size
struct seg { // 1-indexed
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
    }
    void add(int p, ll value) {
        for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) / 2;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
    int kth(int k, int n = 1, int nl = 1, int nr = flag) {
        if (nl == nr) return nl;

        int mid = (nl + nr) / 2;
        if (k <= t[n << 1]) return kth(k, n << 1, nl, mid);
        else return kth(k - t[n << 1], n << 1 | 1, mid + 1, nr);
    }
} seg;

int n, q;
int a[N];
ll qu[Q];
pii ans[Q];

ordered_set st[N];

void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) cin >> qu[i];
}

void solve() {
    vector<int> ord(q);
    iota(all(ord), 1);
    sort(all(ord), [&](int i, int j) {
        return qu[i] < qu[j];
    });

    seg.build(n);
    for (int i = 1; i <= n; i++) {
        seg.add(a[i], 1);
        st[a[i]].insert(i);
    }

    ll cnteq = 0;
    pii eq_example = {-1, -1};
    for (ll i = 1; i <= n; i++) {
        cnteq += (ll)sz(st[i]) * (sz(st[i]) - 1) / 2;
        if (sz(st[i]) >= 2 && eq_example.fr == -1) {
            auto it = st[i].begin();
            eq_example.fr = *(it++);
            eq_example.sc = *it;
        }
    }

    ll acc = 0;

    int idx1 = 1, idx2 = n;
    for (auto &i : ord) {
        ll k = qu[i];

        while (idx1 <= n) {
            int sum = seg.query(1, a[idx1] - 1);
            if (!(sum == 0 || sum < k - acc)) break; 
            acc += sum;
            seg.add(a[idx1], -1);
            st[a[idx1]].erase(idx1);

            idx1++;
        }

        if (idx1 <= n) {
            // assert(idx1 < n);

            int val = seg.kth(k - acc);
            assert(a[idx1] > val);
            ans[i] = {idx1, *(st[val].find_by_order(sz(st[val]) - (k - acc - seg.query(1, val - 1))))};
        } else if (cnteq > 0 && k - acc <= cnteq) {
            ans[i] = eq_example;
        } else {
            acc += cnteq;
            cnteq = 0;

            while (1) {
                int sum = seg.query(a[idx2] + 1, n);
                if (!(sum == 0 || sum < k - acc)) break;
                
                acc += sum;
                seg.add(a[idx2], 1);
                st[a[idx2]].insert(idx2);

                idx2--;

                assert(idx2 >= 1);
            }

            int val = seg.kth(seg.query(1, a[idx2]) + (k - acc));
            assert(a[idx2] < val);
            // if (i == 3) cout << val << ' ' << k - acc - seg.query(a[idx2] + 1, val - 1) << '\n';
            ans[i] = {idx2, *st[val].find_by_order(k - acc - seg.query(a[idx2] + 1, val - 1) - 1)};
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    solve();

    for (int i = 1; i <= q; i++) {
        cout << ans[i].fr << ' ' << ans[i].sc << '\n';
    }
}