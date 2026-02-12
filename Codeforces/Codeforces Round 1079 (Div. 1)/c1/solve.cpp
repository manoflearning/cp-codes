#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

vector<int> query(int k) {
    cout << "? " << k << '\n';
    cout.flush();

    int q; cin >> q;
    vector<int> ret(q);
    for (auto &i : ret) cin >> i;
    return ret;
}

void answer(const set<pii> &e) {
    cout << "! " << sz(e) << '\n';
    for (const auto [u, v] : e) {
        cout << u << ' ' << v << '\n';
    }
    cout.flush();
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        int max_k = -1;
        {
            int l = 1, r = 32768;
            while (l < r) {
                const int mid = (l + r) >> 1;
                if (query(mid).empty()) r = mid;
                else l = mid + 1;
            }
            max_k = l - 1;
        }

        set<pii> e;

        int prv_k = 1;
        pii prv_e = {-1, -1};
        for (int v = 1; v <= n; v++) {
            int u = -1;

            while (1) {
                int l = prv_k + 1, r = max_k;
                while (l < r) {
                    const int mid = (l + r) >> 1;

                    const auto path = query(mid);

                    if (sz(path) < 2 || v != path[0] || u < path[1]) r = mid;
                    else l = mid + 1;
                }
                
                if (l > r) break;

                const auto path = query(l);
                prv_k = l;

                if (sz(path) < 2) break;
                else {
                    u = path[1];
                    e.insert({v, u});
                }
            }
        }

        answer(e);
    }

    return 0;
}
