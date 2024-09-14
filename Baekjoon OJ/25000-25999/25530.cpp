#include <bits/stdc++.h>
using namespace std;

const int MOD = 998'244'353;

int n, k;
vector<int> s, t;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        cin >> n >> k;
        if (n == 0 && k == 0) break;
        s.resize(n);
        t.resize(n);
        for (auto& i : s) cin >> i;
        for (auto& i : t) cin >> i;

        vector<int> rs(n), rt(n);
        for (int i = 0; i < n; i++) {
            rs[s[i]] = i;
            rt[t[i]] = i;
        }

        vector<int> split(n, -1);
        for (int i = 0; i + 1 < n; i++) {
            int u = s[i], v = s[i + 1];
            if (rt[u] < rt[v]) {
                if (u < v) ;
                else split[i + 1] = 0;
            } else {
                split[i + 1] = 1;
            }
        }
    }
}