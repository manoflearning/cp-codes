#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while(tc--) {
        int n, m;
        cin >> n >> m;

        vector<int> cntc(m + 1), cntp(m + 1);

        vector<map<int, int>> mp(m + 1);
        for (int i = 0; i < n; i++) {
            int p; cin >> p;
            cntc[p]++;
            int k; cin >> k;
            while (k--) {
                int x; cin >> x;
                mp[p][x]++;
                cntp[x]++;
            }
        }

        int cnt_free_catnips = 0;
        for (int i = 1; i <= m; i++)
            if (!cntp[i]) cnt_free_catnips++;

        bool yes = 1;
        for (int i = 1; i <= m; i++) {
            if (cntc[i]) {
                for (auto &[k, v] : mp[i]) {
                    cntp[k] -= v;
                    if (cntp[k] == 0) cnt_free_catnips++;
                }

                int opt = -1;

                for (auto &[k, v] : mp[i]) {
                    if (cntp[k] == 0 && cntc[i] == v) {
                        opt = k; break;
                    }
                }

                if (opt == -1) { yes = 0; break; }
                cnt_free_catnips--;
            } else {
                if (cnt_free_catnips == 0) {
                    yes = 0;
                    break;
                }
                cnt_free_catnips--;
            }
        }

        cout << (yes ? "yes" : "no") << '\n';
    }
}