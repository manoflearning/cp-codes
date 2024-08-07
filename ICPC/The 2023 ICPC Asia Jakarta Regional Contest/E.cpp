// C = [3 1 4 5 2 6]
// A = [-INF 3 1 ]
// B = [-INF ]

// C = D1 + D2 + ... + Dm
// Di[0] < Di+1[0] < Di+2[0] < ...

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
vector<int> C, A, B;
vector<vector<int>> D(1);
int dp[2020];

void input() {
    cin >> n;
    C.resize(n << 1);
    for (auto& i : C) cin >> i;
}

void splitC() {
    vector<int> now(1, C[0]);
    for (int i = 1; i < sz(C); i++) {
        if (now[0] < C[i]) {
            D.push_back(now);
            now.clear();
        }
        now.push_back(C[i]);
    }
    D.push_back(now);
}

void bottomup() {
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i < sz(D); i++) {
        int len = sz(D[i]);
        for (int j = len; j <= n; j++) {
            if (dp[j] != -1) continue;
            if (0 <= dp[j - len] && dp[j - len] < i) dp[j] = i;
        }
    }
}

void dpbacktracking() {
    set<int> s;
    
    int p = n;
    while (p >= 1) {
        s.insert(dp[p]);
        p = p - sz(D[dp[p]]);
    }

    for (int i = 1; i < sz(D); i++) {
        if (s.count(i)) for (auto& j : D[i]) A.push_back(j);
        else for (auto& j : D[i]) B.push_back(j);
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

    splitC();

    bottomup();

    if (dp[n] == -1) {
        cout << -1;
        return 0;
    }

    dpbacktracking();

    for (auto& i : A) cout << i << ' ';
    cout << '\n';
    for (auto& i : B) cout << i << ' ';
    cout << '\n';
}