// solution 1: greedy + pq
#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, t, p;
    cin >> n >> t >> p;

    vector<int> a(n);
    for (auto& i : a) cin >> i;

    int ans = 0, tleft = t;
    priority_queue<int> pq;
    int res = 0;
    for (int i = 0; i < n; i++) {
        pq.push(a[i]);
        tleft -= a[i];
        res++;
        while (tleft < 0 && !pq.empty()) {
            tleft += pq.top(); pq.pop();
            res--;
        }
        if (tleft < 0) break;
        ans = max(ans, res);
        tleft -= p;
    }

    cout << ans;
}

// solution 2: parametric search with segment tree
/*#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
struct Seg {
    vector<ll> t;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
    void add(int p, int val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
} seg1, seg2;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, t, p;
    cin >> n >> t >> p;

    vector<int> a(n);
    for (auto& i : a) cin >> i;

    vector<pair<int, int>> b;
    for (int i = 0; i < n; i++) {
        b.push_back({ a[i], i });
    }
    sort(b.begin(), b.end());

    vector<int> Hash(n);
    for (int i = 0; i < n; i++)
        Hash[b[i].second] = i + 1;

    seg1.build(n);
    seg2.build(n);

    ll tleft = t, ans = 0;
    for (int i = 0; i < n; i++) {
        seg1.add(Hash[i], a[i]);
        seg2.add(Hash[i], 1);
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (seg1.query(1, mid) <= tleft) l = mid;
            else r = mid - 1;
        }
        ans = max(ans, seg2.query(1, l));
        tleft -= p;
        if (tleft < 0) break;
    }

    cout << ans;
}*/