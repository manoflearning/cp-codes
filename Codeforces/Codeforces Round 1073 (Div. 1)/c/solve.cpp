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
    bool ret; cin >> ret;
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
            if (res) { i = t; break; }
        }

        if (i == -1) {
            answer({-1});
            continue;
        }

        vector<int> a, b;
        for (int t = 1; t <= i - 1; t++) a.push_back(t);
        
        int tl = j, tr = j + 1;
        while (i < tl || tr <= n) {
            if (i < tl && tr <= n) {
                bool res = query(tl, tr);
                if (res) b.push_back(tl), tl--;
                else b.push_back(tr), tr++;
            } else if (i < tl) {
                b.push_back(tl), tl--;
            } else if (tr <= n) {
                b.push_back(tr), tr++;
            }
        }

        for (int t : b) {
            bool res = query(i, t);
            if (res) { a.push_back(t); break; }
        }
        for (int t : b) {
            if (t != a[i - 1]) a.push_back(t);
            else a.push_back(i);
        }

        answer(a);
    }
}
