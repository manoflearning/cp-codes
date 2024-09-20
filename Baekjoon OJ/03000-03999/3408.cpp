#include <bits/stdc++.h>
using namespace std;

const int MAXN = 202020;

int n;
vector<int> a(MAXN);
vector<int> prv(MAXN), nxt(MAXN);

void init() {}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void prvnxt() {
    map<int, int> last_idx;
    for (int i = 1; i <= n; i++) {
        prv[i] = last_idx[a[i]];
        last_idx[a[i]] = i;
    }
    last_idx.clear();
    for (int i = n; i >= 1; i--) {
        nxt[i] = last_idx[a[i]];
        if (nxt[i] == 0) nxt[i] = n + 1;
        last_idx[a[i]] = i;
    }
}

bool solve(int s, int e) {
    if (s >= e) return 1;

    for (int i = s, j = e; i <= j; i++, j--) {
        if (prv[i] < s && e < nxt[i]) {
            return solve(s, i - 1) && solve(i + 1, e);
        }
        if (prv[j] < s && e < nxt[j]) {
            return solve(s, j - 1) && solve(j + 1, e);
        }
    }

    return 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        prvnxt();

        bool ans = solve(1, n);
        cout << (ans ? "non-boring" : "boring") << '\n';
    }
}
