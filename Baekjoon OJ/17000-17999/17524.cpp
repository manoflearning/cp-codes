#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, k;
vector<pii> a;

void input() {
    cin >> n >> k;
    a.resize(n);
    for (auto& i : a) cin >> i.fr >> i.sc;
}

int cal(int T, pii v) { return 30 + (v.fr - T) * v.sc; }

int sorting(int l, int r) {
    int T1 = INF;
    for (int i = l; i <= r; i++) T1 = min(T1, a[i].fr);

    sort(a.begin() + l, a.begin() + r + 1, [&](const pii& p1, const pii& p2) {
        return cal(T1, p1) < cal(T1, p2);
        // return make_pair(cal(T1, p1), p1) < make_pair(cal(T1, p2), p2);
    });

    return T1;
}

int solve1() {
    int T1 = INF;
    for (auto& i : a) T1 = min(T1, i.fr);
    int ret = 0;
    for (auto& i : a) ret = max(ret, cal(T1, i));
    return ret;
}

int solve2(int l, int r) {
    int T1 = sorting(l, r);

    int ret = INF, T2 = INF;
    for (int i = r - 1; i >= l; i--) {
        T2 = min(T2, a[i + 1].fr);
        int res = 0;
        for (int j = i + 1; j <= r; j++) 
            res = max(res, cal(T2, a[j]));
        res += cal(T1, a[i]);
        ret = min(ret, res);
    }
    return ret;
}

int solve3() {
    int T1 = sorting(0, n - 1);

    int ret = INF;
    for (int i = n - 3; i >= 0; i--) {
        ret = min(ret, cal(T1, a[i]) + solve2(i + 1, n - 1));
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    int ans = solve1();
    if (k >= 2) ans = min(ans, solve2(0, n - 1));
    if (k == 3) ans = min(ans, solve3());

    cout << ans;
}