// sum(l, r) = psum[r] - psum[l - 1] >= x
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int n;
ll x, a[505050], psum[505050];

void input() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }
}

int solve() {
    int ret = INF;

    vector<int> ord(n + 1);
    iota(ord.begin(), ord.end(), 0);

    sort(ord.begin(), ord.end(), [&](int p1, int p2) {
        return psum[p1] > psum[p2];
    });

    set<int> st;
    int j = 0;
    for (int i = 0; i <= n; i++) {
        while (j < n && x <= psum[ord[j]] - psum[ord[i]]) st.insert(ord[j++]);

        auto it = st.upper_bound(ord[i]);
        if (it == st.end()) continue;
        ret = min(ret, *it - ord[i]);
    }
    return (ret == INF ? -1 : ret);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();

        cout << solve() << '\n';
    }
}