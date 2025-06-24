#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;
const int A = 101010;

struct Fenwick { // 0-indexed
    int flag, cnt; // array size
    vector<ll> arr, t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1, cnt++);
        arr.resize(flag);
        t.resize(flag);
    }
    void add(int p, ll value) { // add value at position p
        arr[p] += value;
        while (p < flag) {
            t[p] += value;
            p |= p + 1;
        }
    }
    void modify(int p, ll value) { // set value at position p
        add(p, value - arr[p]);
    };
    ll query(int x) {
        ll ret = 0;
        while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
        return ret;
    }
    ll query(int l, int r) {
        return query(r) - (l ? query(l - 1) : 0);
    }
} fw;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    fw.build(A + 1);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        ll ans = 0;

        for (int j = n - 1; j >= 0; j--) {
            for (int i = j - 1; i >= 0; i--) {
                int k_lb = a[n - 1] - (a[i] + a[j]) + 1;
                int k_ub = (a[i] + a[j]) - 1;

                k_lb = max(k_lb, 1);
                k_ub = min(k_ub, A);
                if (k_lb > k_ub) continue;
                ans += fw.query(k_lb, k_ub);
            }
            fw.add(a[j], 1);
        }

        cout << ans << '\n';

        for (auto &i : a) fw.modify(i, 0);
    }
}
