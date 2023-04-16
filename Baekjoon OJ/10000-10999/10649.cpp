// solution 2 : bitmask DP
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node { ll h, w, p; };

int n;
ll h;
vector<Node> a;
ll dp[1 << 20];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> h;
    a.resize(n);
    for (auto& i : a)
        cin >> i.h >> i.w >> i.p;

    memset(dp, -1, sizeof(dp));
    dp[0] = 1e9 + 7;
    ll ans = -1;
    for (int i = 1; i < (1 << n); i++) {
        ll sumh = 0;
        for (int j = 0; j < n; j++) {
            if (!(i & (1 << j))) continue;
            if (dp[i - (1 << j)] >= a[j].w) {
                dp[i] = max(dp[i], min(dp[i - (1 << j)] - a[j].w, a[j].p));
            }
            sumh += a[j].h;
        }

        if (sumh >= h) ans = max(ans, dp[i]);
    }
    if (ans == -1) cout << "Mark is too tall";
    else cout << ans;
}

// solution 1 : backtracking + greedy (exchange argument)
/*#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node { ll h, w, p; };

int n;
ll h;
vector<Node> a;

vector<int> res;
ll cal() {
    vector<int> arr = res;
    sort(arr.begin(), arr.end(), [&](int v1, int v2) {
        return a[v1].p + a[v1].w > a[v2].p + a[v2].w;
    });

    ll sumH = 0, mnp = 1e9 + 7;
    for (auto& i : arr) {
        if (mnp < a[i].w) return -1;
        mnp = min(mnp - a[i].w, a[i].p);
        sumH += a[i].h;
    }
    if (sumH < h) return -1;
    return mnp;
}

ll f(int x) {
    if (x == n) return cal();
    ll ret = -1;
    ret = max(ret, f(x + 1));
    res.push_back(x);
    ret = max(ret, f(x + 1));
    res.pop_back();
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> h;
    a.resize(n);
    for (auto& i : a)
        cin >> i.h >> i.w >> i.p;

    ll res = f(0);
    if (res == -1) cout << "Mark is too tall";
    else cout << res;
}*/