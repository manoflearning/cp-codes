#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MAXN = 1e5 + 10;
constexpr int MOD = 998'244'353;

bool is_prime[MAXN];
ll pd[MAXN];
ll cal_period(ll x) {
    if (x == 2 || x == 5) return 1;
    ll st = 1;
    ll now = st;
    ll period = 0;
    do {
        period++;
        now = now * 10 % x;
    } while(st != now);
    return period;
}
int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    fill(is_prime, is_prime + MAXN, 1);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < MAXN; i++) {
        if(is_prime[i]) {
            pd[i] = cal_period(i);

            if (i == 2 || i == 5) continue;

            for(int np = 2 * i; np < MAXN; np += i) {
                is_prime[np] = false;
                pd[np] = max(pd[np], pd[i]);
            }
        }
    }
    
    cout << cal_period(7) << ' ' << cal_period(11) << '\n';
}