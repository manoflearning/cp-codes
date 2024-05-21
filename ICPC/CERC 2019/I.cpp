#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

string s, t;
int n, a[1010101], b[1010101];
ll cnt[4][4], ans = 0;

void input() {
    cin >> s >> t;
    n = sz(s);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') a[i] = 0;
        else if (s[i] == 'C') a[i] = 1;
        else if (s[i] == 'G') a[i] = 2;
        else if (s[i] == 'T') a[i] = 3;
    }
    for (int i = 0; i < n; i++) {
        if (t[i] == 'A') b[i] = 0;
        else if (t[i] == 'C') b[i] = 1;
        else if (t[i] == 'G') b[i] = 2;
        else if (t[i] == 'T') b[i] = 3;
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) continue;
        cnt[a[i]][b[i]]++;
    }

    vector<vector<int>> len2, len3, len4;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            len2.push_back({ i, j });

            for (int k = 0; k < 4; k++) {
                if (k == i || k == j) continue;

                len3.push_back({ i, j, k });
                
                for (int p = 0; p < 4; p++) {
                    if (p == i || p == j || p == k) continue;
                    len4.push_back({ i, j, k, p });
                }
            }
        }
    }

    // |cycle| = 2
    for (auto& i : len2) {
        int u = i[0], v = i[1];
        ll res = min(cnt[u][v], cnt[v][u]);
        ans += res;
        cnt[u][v] -= res;
        cnt[v][u] -= res;
    }

    // |cycle| = 3
    for (auto& i : len3) {
        int u = i[0], v = i[1], p = i[2];
        ll res = min({ cnt[u][v], cnt[v][p], cnt[p][u] });
        ans += res * 2;
        cnt[u][v] -= res;
        cnt[v][p] -= res;
        cnt[p][u] -= res;
    }

    // |cycle| = 4
    for (auto& i : len4) {
        int u = i[0], v = i[1], p = i[2], q = i[3];
        ll res = min({ cnt[u][v], cnt[v][p], cnt[p][q], cnt[q][u] });
        ans += res * 3;
        cnt[u][v] -= res;
        cnt[v][p] -= res;
        cnt[p][q] -= res;
        cnt[q][u] -= res;
    }

    // assertion
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(cnt[i][j] == 0);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}