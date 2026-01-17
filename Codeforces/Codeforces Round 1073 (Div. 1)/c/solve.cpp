#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool query(int i, int j) {
    cout << "? " << i << ' ' << j << '\n';
    cout.flush();
    int ret; cin >> ret;
    assert(ret != -1);
    return ret;
}

void answer(vector<int> ans) {
    cout << "! ";
    for (auto &i : ans) cout << i << ' ';
    cout << '\n';
    cout.flush();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        assert(n != -1);

        int j = -1;
        for (int t = n - 1; t >= 1; t--) {
            bool res = query(t, t + 1);
            if (!res) { j = t + 1; break; }
        }

        if (j == -1) {
            answer({-1});
            continue;
        }

        int i = -1, k = -1;
        for (int t = j - 2; t >= 1; t--) {
            bool res = query(t, t + 1);
            if (res) {
                i = t, k = j;
                for (int x = t + 2; x <= j; x++) {
                    if (!query(i, x)) {
                        k = x - 1;
                        break;
                    }
                }
                break;
            }
        }

        if (i == -1) {
            answer({-1});
            continue;
        }

        vector<int> ans;

        for (int t = 1; t <= i - 1; t++) ans.push_back(t);
        ans.push_back(k);

        int tl = j, tr = j + 1;
        while (i < tl || tr <= n) {
            const int u = (tl == k ? i : tl);
            const int v = tr;
            if (i < tl && tr <= n) {
                bool res = query(u, v);
                if (res) ans.push_back(u), tl--;
                else ans.push_back(v), tr++;
            } else if (i < tl) {
                ans.push_back(u), tl--;
            } else if (tr <= n) {
                ans.push_back(v), tr++;
            }
        }

        answer(ans);
    }
}
