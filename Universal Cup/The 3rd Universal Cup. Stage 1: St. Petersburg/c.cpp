#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 101010, R = 101010;

// int flag;
// struct Seg {
//     vector<ll> t;
//     void init() {
//         for (flag = 1; flag < N; flag <<= 1);
//         t.resize(flag << 1);
//     }
//     void modify(int p, int val) {
//         for (t[p += flag - 1] = val; p > 1; p >>= 1)
//             t[p >> 1] = t[p] + t[p ^ 1];
//     }
//     ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
//         if (nr < l || r < nl) return 0;
//         if (l <= nl && nr <= r) return t[n];
//         int mid = (nl + nr) >> 1;
//         return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
//     }
// }seg;

int n, k;
int r[N];
vector<int> rev_r[R];
string s;
set<int> st0;

map<pair<int, int>, int> pq_idx;
vector<priority_queue<int>> pqs;
priority_queue<int> du;

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
        rev_r[r[i]].push_back(i);
    }
    cin >> s;
    s = "0" + s;
}

int rightmost(int ub) { // [1, ub]
    auto it = st0.upper_bound(ub);
    it--;
    return *it;
}
int leftmost(int lb) { // [lb, N]
    auto it = st0.lower_bound(lb);
    return *it;
}
// int get_rating(int lb) { // [lb, R]
//     auto it = ratings.lower_bound(lb);
//     return *it;
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    // seg.init();

    st0.insert(0);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') st0.insert(i);
    }
    st0.insert(n + 1);

    int ans = 0;

    pqs.push_back(du);
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') continue;

        int ss = rightmost(i - 1) + 1;
        int ee = leftmost(i + 1) - 1;

        priority_queue<int> pq;
        for (int j = ss; j <= ee; j++) pq.push(-r[j]);
        while (sz(pq) > k) pq.pop();

        pq_idx[{ ss, ee }] = sz(pqs);
        pqs.push_back(pq);

        if (sz(pq) >= k) {
            ans = max(ans, -pq.top());
        }
    }

    for (int i = 1; i < R; i++) {
        for (auto& j : rev_r[i]) {
            if (s[j] == '0') st0.erase(j);
        }

        for (auto& j : rev_r[i]) {
            if (s[j] != '0') continue;

            int ss = rightmost(j - 1) + 1;
            int ee = leftmost(j + 1) - 1;

            auto& pql = pqs[pq_idx[{ ss, j - 1 }]];
            auto& pqr = pqs[pq_idx[{ j + 1, ee }]];

            if (ss > j - 1) pql = du;
            if (j + 1 > ee) pqr = du;

            if (ss > j - 1 && j + 1 > ee) continue;

            while (!pql.empty() && -pql.top() <= i) pql.pop();
            while (!pqr.empty() && -pqr.top() <= i) pqr.pop();

            pq_idx[{ ss, ee }] = pq_idx[{ j + 1, ee }];

            if (sz(pql) > sz(pqr)) {
                swap(pql, pqr);
                pq_idx[{ ss, ee }] = pq_idx[{ ss, j - 1 }];
            }

            while (!pql.empty()) {
                pqr.push(pql.top());
                pql.pop();
            }
            while (sz(pqr) > k) pqr.pop();

            if (sz(pqr) >= k) {
                ans = max(ans, -pqr.top());
            }
        }
    }

    cout << ans;
}
