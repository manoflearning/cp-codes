#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 505050;
const int MAXQ = 101010;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int N, a[MAXN];
map<int, int> pgcd[MAXN], sgcd[MAXN];
ll psum[MAXN];
ll ans[MAXQ];

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
}

void getAllPrefixGcd() {
    pgcd[1][a[1]]++;
    for (int i = 2; i <= N; i++) {
        for (auto& j : pgcd[i - 1]) {
            int x = j.fr, cnt = j.sc;
            x = gcd(x, a[i]);
            pgcd[i][x] += cnt;
        }
        pgcd[i][a[i]]++;
    }

    sgcd[N][a[N]]++;
    for (int i = N - 1; i >= 1; i--) {
        for (auto& j : sgcd[i + 1]) {
            int x = j.fr, cnt = j.sc;
            x = gcd(x, a[i]);
            sgcd[i][x] += cnt;
        }
        sgcd[i][a[i]]++;
    }
}

void buildPsum() {
    for (int i = 1; i <= N; i++) {
        psum[i] = psum[i - 1];
        for (auto& j : pgcd[i])
            psum[i] += (ll)j.fr * j.sc;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getAllPrefixGcd();

    buildPsum();

    int q; cin >> q;
    for (int i = 1; i <= q; i++) {
        ll l, r;
        cin >> l >> r;
        l ^= ans[i - 1], r ^= ans[i - 1];
        
        ans[i] += psum[r] - psum[l - 1];

        vector<pii> arr;
        for (auto& j : sgcd[l]) {
            arr.push_back(j);
        }
        sort(arr.rbegin(), arr.rend());

        int cnt = 0;
        for (auto& j : arr) {
            if (r - l + 1 < cnt) break;
            for (auto& k : pgcd[l - 1]) {
                ans[i] -= min<ll>(j.sc, r - l + 1 - cnt) * k.sc * gcd(j.fr, k.fr);
            }
            cnt += j.sc;
        }

        cout << ans[i] << '\n';
    }
}