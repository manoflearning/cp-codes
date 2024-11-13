#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXC = 1010101;
const int MAXM = 56;

int c, n, m;
vector<ll> a;

ll dp1[MAXM];
ll dp2[MAXC / 1000][MAXM];

void input() {
    cin >> c >> n >> m;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push_back(x);
    }
}

void bottomup() {
    // base case
    for (auto x : a) {
        for (int j = 0; j <= 54; j++) {
            if (c < x) {
                dp2[(x / 2 + 999) / 1000][j]++;
                dp2[x / 2 / 1000][j]++;
                break;
            } else dp1[j]++;
            x *= 2;
        }
    }

    // inductive step
    for (int i = 0; i < MAXC / 1000; i++) {
        for (int j = 0; j + 1 <= 54; j++) {
            if (c < i * 1000 * 2) {
                dp2[i][j + 1] += 2 * dp2[i][j];
            } else {
                dp2[i * 2][j + 1] += dp2[i][j];
            }
        }
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
    
    bottomup();

    while (m--) {
        int x; cin >> x;

        ll ans = 0;
        ans += dp1[x];
        for (int i = 0; i < MAXC / 1000; i++) {
            ans += dp2[i][x];
        }

        cout << ans << '\n';
    }
}
