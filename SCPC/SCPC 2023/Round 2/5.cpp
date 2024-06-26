#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
#define pii pair<int, int>
#define fr first
#define sc second

int N, K, M;
vector<pii> edges;
ll ans = 0;

void init() {
    ans = 0;
}

void input() {
    cin >> N >> K >> M;
    edges.resize(M);
    for (auto& i : edges) cin >> i.fr >> i.sc;
}

void group1() {
    vector<int> a(N + 1);
    for (int i = 1; i <= N; i++) a[i] = i;
    do {
        int isValid = 1;
        for (auto& i : edges) {
            if (K < a[i.fr] + a[i.sc]) { isValid = 0; break; }
        }
        ans += isValid;
    } while (next_permutation(a.begin() + 1, a.end()));
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    // freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    // #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        if (N <= 8) group1();
        else ;

        cout << ans << '\n';

        cout << flush;
    }
}