#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int MOD = 1e9 + 7;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> h(n), b(m);
    for (auto &i : h) cin >> i;
    for (auto &i : b) cin >> i;

    sort(all(h));
    sort(all(b));

    multiset<int> st;
    for (auto &i : b) st.insert(i);

    bool ans = 1;
    for (int i = 0; i < k; i++) {
        auto it = st.lower_bound(h[i]);

        if (it == st.end()) {
            ans = 0;
            break;
        }

        st.erase(it);
    }

    cout << (ans ? "Yes" : "No");
}