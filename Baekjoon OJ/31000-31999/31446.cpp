#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;

int n;
ll s;

void solve(int h) {
    int x = s / h;
    if (x <= 2) return;
    x -= 1;

    vector<pii> res;
    res.push_back({ 0, 0 });
    for (int j = 0; j < n - 2; j++) {
        int y = (j + 1) / 2;
        if (j == n - 3) y = h;
        if (j & 1) res.push_back({ 1, y });
        else res.push_back({ x, y });
    }
    res.push_back({ 0, h });

    bool is_valid = 1;
    ll area = 0;
    for (auto& i : res) {
        is_valid &= (i.second <= h);
    }
    for (int i = 1; i + 1 < sz(res); i++) {
        area += abs(res[i].first * res[i + 1].second - res[i + 1].first * res[i].second);
    }
    is_valid &= area == s;
    is_valid &= (res[sz(res) - 3].second != res[sz(res) - 2].second);

    if (is_valid) {
        cout << "YES\n";
        for (auto& i : res)
            cout << i.first << ' ' << i.second << '\n';
        exit(0);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;

    if (n == 3) {
        cout << "YES\n";
        cout << 0 << ' ' << s << '\n';
        cout << 0 << ' ' << 0 << '\n';
        cout << 1 << ' ' << 0 << '\n';
        return 0;
    }

    for (int i = 1; i * i <= s; i++) {
        if (s % i) continue;

        solve(i);
        solve(s / i);
    }

    cout << "NO\n";
}