#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const char VOWS[] = { 'A', 'E', 'I', 'O', 'U', 'Y' };
const int INF = 1e9 + 7;

const int N = 1010101;

int n;
vector<bool> a[N];
int dp[N][3];

bool is_vowel(char c) {
    for (int i = 0; i < 6; i++)
        if (c == VOWS[i]) return 1;
    return 0;
}

int f(int idx, int cnt) {
    int& ret = dp[idx][cnt];
    if (ret != -1) return ret;
    if (idx == n + 1) return ret = 0;
    
    ret = INF;
    for (int i = 0; i < sz(a[idx]); i++) {
        if (a[idx][i]) cnt = 0;
        else cnt++;

        if (cnt == 3) break;

        ret = min(ret, i + 1 + f(idx + 1, cnt));
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

    cin >> n;

    for (int i = 1; i <= n; i++) {
        string s; cin >> s;

        for (int j = 0; j < min(3, sz(s)); j++) {
            a[i].push_back(is_vowel(s[j]));
        }
    }

    int ans = f(1, 0);

    if (ans == INF) cout << '*';
    else cout << ans;
}