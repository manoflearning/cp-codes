#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int query(const vector<int> &st) {
    cout << "? " << sz(st) << ' ';
    for (auto &i : st) cout << i << ' ';
    cout << '\n';
    cout.flush();

    int ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> ans(2 * n + 1);

        vector<int> st;
        st.push_back(1);

        for (int i = 2; i <= 2 * n; i++) {
            st.push_back(i);

            if (sz(st) == 1) continue;

            int res = query(st);
            if (res == 0) {
                continue;
            } else {
                if (sz(st) == 2) {
                    ans[st.back()] = res;
                    st.pop_back();
                    ans[st.back()] = res;
                    st.pop_back();
                } else {
                    ans[st.back()] = res;
                    st.pop_back();
                }
            }
        }

        vector<int> st2, vis(n + 1);
        for (int i = 1; i <= 2 * n; i++) {
            if (ans[i] && !vis[ans[i]]) {
                st2.push_back(i);
                vis[ans[i]] = 1;
            }
        }

        assert(sz(st2) >= n);

        for (auto &i : st) {
            st2.push_back(i);
            int res = query(st2);
            ans[i] = res;
            st2.pop_back();
        }

        cout << "! ";
        for (int i = 1; i <= 2 * n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
        cout.flush();

    }
}

// ? [l, r] => n

// 3n = 2n + n