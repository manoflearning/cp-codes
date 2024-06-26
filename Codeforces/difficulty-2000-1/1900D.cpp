#pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int gcd(int x, int y) {
    if (!y) return x;
    return gcd(y, x % y);
}

int n;
vector<int> a;
vector<ll> sum(101010), psum(101010);
vector<ll> p[101010];

void preprocessing() {
    for (int i = 2; i < 101010; i++) {
        int tmp = i;
        if (tmp % 2 == 0) {
            p[i].push_back(2);
            while (tmp % 2 == 0) tmp /= 2;
        }
        for (int x = 3; x * x <= tmp; x += 2) {
            if (tmp % x == 0) {
                p[i].push_back(x);
                while (tmp % x == 0) tmp /= x;
            }
        }
        if (tmp > 1) p[i].push_back(tmp);
    }
}

void init() {
    for (int i = 0; i < 101010; i++) {
        sum[i] = psum[i] = 0;
    }
}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

ll naive() {
    ll ret = 0;
    sort(all(a));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ret += (n - j - 1) * gcd(a[i], a[j]);
        }
    }
    return ret;
}

ll solve() {
    ll ret = 0;

    for (auto& i : a) sum[i]++;
    for (int i = 101010 - 2; i >= 0; i--)
        psum[i] += sum[i] + psum[i + 1];

    for (ll d = 1; d < 101010; d++) {
        unordered_map<int, ll> mp;

        for (int i = d, j = 1; i < 101010; i += d, j++) { // O(nsqrtn)
            if (!sum[i]) continue;
            if (psum[i] <= 1) break;

            ll currAns = 0;

            ll prvCnt = 0;
            for (int bit = 0; bit < (1 << sz(p[j])); bit++) {
                int cnt = 0, res = 1;
                for (int b = 0; b < sz(p[j]); b++) {
                    if ((1 << b) & bit) cnt++, res *= p[j][b];
                }

                if (cnt & 1) prvCnt -= mp[res];
                else prvCnt += mp[res];
            }

            currAns += (__int128_t)d * prvCnt * sum[i] * (sum[i] - 1) / 2; // a < b = c
            currAns += (__int128_t)d * prvCnt * sum[i] * psum[i + 1]; // a < b < c

            for (int bit = 0; bit < (1 << sz(p[j])); bit++) {
                int res = 1;
                for (int b = 0; b < sz(p[j]); b++) {
                    if ((1 << b) & bit) res *= p[j][b];
                }
                mp[res] += sum[i];
            }

            // cout << i << ' ' << currAns << '\n';

            ret += currAns;
        }
    }
    // 4734602074359455760

    for (ll x = 1; x + 1 < 101010; x++) {
        ret += (__int128_t)x * sum[x] * (sum[x] - 1) / 2 * psum[x + 1]; // a = b < c
        ret += (__int128_t)x * sum[x] * (sum[x] - 1) * (sum[x] - 2) / 6; // a = b = c
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

    preprocessing();

    // cout << "4734602074359455760" << '\n';
    // cout << LLONG_MAX << '\n';
    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        // cout << naive() << '\n';

        cout << solve() << '\n';
    }
}