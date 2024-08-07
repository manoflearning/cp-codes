// 1 ~ K ~ 2K
// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

ll X;
int ans[404], flag;

void init() {
    memset(ans, 0, sizeof(ans));
    flag = 0;
}

void input() { cin >> X; }

void solve(ll now) {
    vector<ll> p;
    int sum = 0;
    for (int i = 2; i <= sqrt(now); i++) {
        while (now % i == 0) {
            p.push_back(i);
            now /= i;
            sum += i;
        }
    }
    if (now > 1) p.push_back(now);

    if (400 - flag < sum + 1) {
        ans[flag++] = 1;
        ans[flag++] = 0;
        ans[flag++] = 1;
        solve((now + 1) / 2);
    }
    else {
        ans[flag++] = 1;
        for (auto& i : p) {
            for (int j = 0; j < i; j++) {
                if (j == i - 1) ans[flag++] = 1;
                else ans[flag++] = 0;
            }
        }
    }
}

void print() {
    int K = 0;
    for (int i = 0; i < flag; i++) K += ans[i];

    cout << flag << ' ' << K << '\n';
    for (int i = 0; i < flag; i++) cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        solve(X);

        print();

        cout << flush;
    }
}