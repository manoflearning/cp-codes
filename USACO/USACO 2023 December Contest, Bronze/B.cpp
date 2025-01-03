#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n;
string s;
vector<int> lens;
int ti = 1e9 + 7;
int ans = 0;

void input() { cin >> n >> s; }

void solve() {
    int len = 0;
    for (auto& c : s) {
        if (c == '1') len++;
        if (c == '0') {
            if (len > 0) lens.push_back(len);
            len = 0;
        }
    }
    if (len > 0) lens.push_back(len);

    for (int i = 0; i < lens.size(); i++) {
        int len = lens[i];
        if ((i == 0 && s[0] == '1') || (i == sz(lens) - 1 && s[n - 1] == '1')) {
            ti = min(ti, len - 1);
        }
        else ti = min(ti, (len + 1) / 2 - 1);
    }

    for (auto& len : lens) {
        int div = 2 * ti + 1;
        ans += (len + div - 1) / div;
    }
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}