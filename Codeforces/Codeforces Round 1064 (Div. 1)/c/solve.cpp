#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 505050;
constexpr int Q = 50505;
constexpr int D = 20;

template <class T, class O = less<T>>
struct pq_set {
  priority_queue<T, vector<T>, O> q, del;
  const T &top() const { return q.top(); }
  int size() const { return int(q.size() - del.size()); }
  bool empty() const { return !size(); }
  void insert(const T x) { q.push(x), flush(); }
  void pop() { q.pop(), flush(); }
  void erase(const T x) { del.push(x), flush(); }
  void flush() {
    while (del.size() && q.top() == del.top()) q.pop(), del.pop();
  }
};

ll _hash(ll x, int i) {
    return (x << D) + i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n), c(q);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < q; i++) cin >> c[i];

        struct state {
            pq_set<ll> pq;
            int cnt;
        };
        vector<state> arr(30);
        for (int i = 0; i < n; i++) {
            for (int b = 0; b < 30; b++) {
                if (a[i] & (1 << b)) arr[b].cnt++;
                arr[b].pq.insert(_hash(a[i] & ((1 << b) - 1), i));
            }
        }

        for (int i = 0; i < q; i++) {
            int ans = 0;

            vector<pii> restore;
            for (int k = 29; k >= 0; k--) {
                bool x = (c[i] & (1 << k) ? 1 : 0);

                if (arr[k].cnt >= 2 || (!x && arr[k].cnt)) break;

                if (x && !arr[k].cnt) {
                    if (sz(restore) < n) {
                        ll hashed = arr[k].pq.top();
                        int v = hashed >> D;
                        int idx = hashed & ((1 << D) - 1);
                        ans += (1 << k) - v;

                        for (int b = 0; b < k; b++) {
                            if (a[idx] & (1 << b)) arr[b].cnt--;
                            arr[b].pq.erase(_hash(a[idx] & ((1 << b) - 1), idx));
                        }
                        restore.push_back({idx, k});
                    } else {
                        ans += (1 << k);
                    }
                }
            }

            cout << ans << '\n';

            for (const auto &[idx, k] : restore) {
                for (int b = 0; b < k; b++) {
                    if (a[idx] & (1 << b)) arr[b].cnt++;
                    arr[b].pq.insert(_hash(a[idx] & ((1 << b) - 1), idx));
                }
            }
        }
    }
}

// a[0] = 00011
// a[1] = 00011
// a[2] = 00011
// c[0] = 11100
