#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXS = 101010;

string s;
ll ssum[MAXS], ssum2[MAXS];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s;

    while (!s.empty() && s.back() == 'R') s.pop_back();

    for (int i = sz(s) - 1; i >= 0; i--) {
        ssum[i] = (s[i] == 'L') + ssum[i + 1];
        if (s[i] == 'R') {
            ssum2[i] = ssum2[i + 1] + 1;
        }
        else {
            ssum2[i] = max(0ll, ssum2[i + 1] - 1);
        }
    }

    ll ans1 = 0, ans2 = 0;
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == 'R') {
            ans1 = max(ans1, ssum[i] + ssum2[i] - 1);
            ans2 += ssum[i];
        }
    }

    cout << ans1 << ' ' << ans2;
}
