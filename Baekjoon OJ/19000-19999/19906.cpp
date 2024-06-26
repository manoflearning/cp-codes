#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

int n, m, a[303030];
vector<int> idx[303030];
vector<pii> arr;
vector<int> L(303030, 1e9 + 7), R(303030, 0);
vector<pair<int, pii>> b;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        idx[a[i]].push_back(i);
        L[a[i]] = min(L[a[i]], i);
        R[a[i]] = max(R[a[i]], i);
    }

    for (int i = 1; i <= m; i++) {
        if (idx[i].size() < 2) continue;
        for (int j = 0; j + 1 < idx[i].size(); j++) {
            int u = idx[i][j], v = idx[i][j + 1];
            arr.push_back({ u, v });
        }
    }

    sort(arr.begin(), arr.end(), [&](const pii& lhs, const pii& rhs) {
        return lhs.fr ^ rhs.fr ? lhs.fr < rhs.fr : lhs.sc > rhs.sc;
    });

    set<int> s;
    for (int i = 0; i < arr.size(); i++) {
        auto [u, v] = arr[i];
        if (s.upper_bound(u) != s.lower_bound(v)) {
            cout << -1;
            return 0;
        }
        s.insert(v);
    }

    
    for (int i = 1; i <= m; i++) {
        if (n < L[i]) continue;
        b.push_back({ i, { L[i], R[i] }});
    }

    sort(b.begin(), b.end(), [&](const pair<int, pii>& lhs, const pair<int, pii>& rhs) {
        return (lhs.sc.sc - lhs.sc.fr) > (rhs.sc.sc - rhs.sc.fr);
    });

    cout << b.size() << '\n';
    for (auto& i : b) {
        cout << i.fr << ' ' << i.sc.fr << ' ' << i.sc.sc << '\n';
    }
}