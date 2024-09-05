#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 1010;
const ll INF = 1e18;

int n;
ll w[MAXN][MAXN];

ll score_1 = 0, score_2 = 0;
ll w_1[MAXN], w_2[MAXN];

ll case1() {
    set<int> st_1, st_2;
    st_1.insert(1);
    for (int i = 2; i <= n; i++) st_2.insert(i);

    while (sz(st_1) < sz(st_2)) {
        for (auto& i : st_2) {
            w_1[i] = w_2[i] = 0;
            for (auto& j : st_1) w_1[i] += w[i][j];
            for (auto& j : st_2) w_2[i] += w[i][j];
        }

        int opt = -1; ll opt_val = -INF;
        for (auto& i : st_2) {
            ll val = w_1[i] - w_2[i];
            if (opt_val < val) {
                opt = i, opt_val = val;
            }
        }

        st_1.insert(opt);
        st_2.erase(opt);
    }

    ll ret = 0;
    for (auto& i : st_1)
        for (auto& j : st_1) if (i < j) ret -= w[i][j];
    for (auto& i : st_2)
        for (auto& j : st_2) if (i < j) ret += w[i][j];
    
    return ret;
}

ll case2() {
    set<int> st_1, st_2;
    st_1.insert(1);
    for (int i = 2; i <= n; i++) st_2.insert(i);

    while (sz(st_1) < sz(st_2)) {
        for (auto& i : st_2) {
            w_1[i] = w_2[i] = 0;
            for (auto& j : st_1) w_1[i] += w[i][j];
            for (auto& j : st_2) w_2[i] += w[i][j];
        }

        int opt = -1; ll opt_val = INF;
        for (auto& i : st_2) {
            ll val = w_1[i] - w_2[i];
            if (opt_val > val) {
                opt = i, opt_val = val;
            }
        }

        st_1.insert(opt);
        st_2.erase(opt);
    }

    ll ret = 0;
    for (auto& i : st_1)
        for (auto& j : st_1) if (i < j) ret += w[i][j];
    for (auto& i : st_2)
        for (auto& j : st_2) if (i < j) ret -= w[i][j];
    
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }

    cout << max(case1(), case2());
}