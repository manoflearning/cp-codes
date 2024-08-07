#include <bits/stdc++.h>
using namespace std;

int N;
int nxt[202020], dp[202020];
int ind[202020], vi[202020];

int f(int v) {
    int& ret = dp[v];
    if (ret != -1) return ret;
    return ret = 1 + f(nxt[v]);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

    cin >> N;

    for (int i = 1; i <= N; i++) {
        string s = to_string(i);
        for (auto& j : s) nxt[i] += j - '0';
        nxt[i] += i;
        if (nxt[i] > N) nxt[i] -= N;
        ind[nxt[i]]++;
    }

    queue<int> q;
    for (int v = 1; v <= N; v++)
        if (!ind[v]) q.push(v);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        vi[v] = 1;

        int u = nxt[v];
        ind[u]--;
        if (!ind[u]) q.push(u);
    }

    for (int i = 1; i <= N; i++) {
        if (vi[i]) continue;
        if (dp[i] != -1) continue;
        int v = i, len = 0;
        while (1) {
            v = nxt[v];
            len++;
            if (v == i) break;
        }
        while (1) {
            v = nxt[v];
            dp[v] = len;
            if (v == i) break;
        }
    }

    int ans = 0;
    for (int v = 1; v <= N; v++) {
        if (vi[v]) ans = max(ans, f(v));
        else ans = max(ans, dp[v]);
    }

    cout << ans;
}