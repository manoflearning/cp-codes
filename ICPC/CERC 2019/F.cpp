#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

ll N, M;
ll ans = 0;

void input() { cin >> N >> M; }

ll sum1ton(ll n) { return n * (n + 1) / 2; };

ll f(ll UB) {
    if (UB == 0) return 0;
    int ret = 0;
    for (ll x = 1; x * x <= UB; x++) {
        ret += sum1ton(UB / x);
        ll y = UB / x;
        if (UB % x == 0) ret += sum1ton(UB / y) * x;
        else {
            ret += sum1ton(UB / y) * x;
            ret += (UB % x ) * (UB / y);
        }
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

    input();

    cout << f(M) - f(N - 1);
}