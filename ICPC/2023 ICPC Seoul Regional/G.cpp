#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int N, K, M, F;
set<int> st[111];
map<string, vector<int>> mp;

void input() {
    cin >> N >> K >> M >> F;
    for (int i = 1; i <= K; i++) {
        int cnt = M;
        while (cnt--) {
            int x; cin >> x;
            st[i].insert(x);
        }
    }
}

void buildMap() {
    for (int x = 1; x <= N; x++) {
        string res;
        for (int i = 1; i <= K; i++) {
            if (st[i].count(x)) res.push_back('Y');
            else res.push_back('N');
        }
        mp[res].push_back(x);
    }
}

void solve() {
    for (int i = 0; i < F; i++) {
        string s; cin >> s;
        if (sz(mp[s]) == 1) cout << mp[s][0] << '\n';
        else cout << 0 << '\n';
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

    buildMap();

    solve();
}