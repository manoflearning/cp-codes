#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rep(i, n) for(int i = 0; i < (n); i++)

const ll MOD = 998244353;
const int MAXN = 101010;

ll m[MAXN], s[MAXN], o[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // preprocessing
    m[1] = 1, s[1] = 1; o[1] = 2;
    for(int i = 2; i < MAXN; i++){
        m[i] = (1 + m[i - 1] + o[i - 1]) % MOD;
        s[i] = (1 + s[i - 1] + o[i - 1]) % MOD;
        o[i] = (2 + 3 * o[i - 1]) % MOD;
    }

    int tc; cin >> tc;
    while(tc--){
        int n; cin >> n;
        vector<ll> a(n), b(n);
        rep(i, n) cin >> a[i];
        rep(i, n) cin >> b[i];

        if (a == b) {
            cout << 0 << '\n';
            continue;
        }

        ll ans = 0;
        bool p = 0, vis = 0;
        for(int i = n - 1; i>= 0; i--){
            p = 1 - p;
            if(a[i] == b[i] && !vis) continue;
            vis = 1;
            if(p){
                if(b[i] == 2) ans = (ans + m[i + 1]) % MOD;
                if(a[i] == 2) ans = (ans + s[i + 1]) % MOD;
                if(a[i] != 2 && b[i] != 2) ans = (ans + o[i + 1]) % MOD;
            }
            else{
                if(b[i] == 2) ans = (ans - m[i + 1] + MOD) % MOD;
                if(a[i] == 2) ans = (ans - s[i + 1] + MOD) % MOD;
                if(a[i] != 2 && b[i] != 2) ans = (ans - o[i + 1] + MOD) % MOD;
            }
        }
        cout << (ans  + MOD) % MOD << '\n';
    }
}
