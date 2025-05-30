#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;
const int MOD = 998'244'353;

int n, c[MAXN], a[MAXN];
ll fac[MAXN];

void init() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = i * fac[i - 1] % MOD;
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> c[i] >> a[i];
}

void solve() {
    map<int, int> diff;
    for (int i = 1; i <= n; i++)
        diff[c[i] - a[i]]++;

    ll cnt = 1;
    for (auto& i : diff)
        cnt = cnt * fac[i.second] % MOD;

    vector<int> ord;
    for (int i = 1; i <= n; i++)
        ord.push_back(i);
    
    sort(ord.begin(), ord.end(), [&](int p1, int p2) {
        return c[p1] - a[p1] > c[p2] - a[p2];
    });

    ll l = 0, r = n - 1;
    ll score = 0;
    for (auto& i : ord) {
        score += c[i] * l + a[i] * r;
        l++, r--;
    }

    cout << score << ' ' << cnt << '\n';
    for (auto& i : ord) cout << i << ' ';
    cout << '\n';

    sort(ord.begin(), ord.end(), [&](int p1, int p2) {
        return c[p1] - a[p1] < c[p2] - a[p2];
    });

    l = 0, r = n - 1;
    score = 0;
    for (auto& i : ord) {
        score += c[i] * l + a[i] * r;
        l++, r--;
    }

    cout << score << ' ' << cnt << '\n';
    for (auto& i : ord) cout << i << ' ';
    cout << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    solve();
}