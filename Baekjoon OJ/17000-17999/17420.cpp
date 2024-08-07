//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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

const int MAXN = 101010;

int n;
ll a[MAXN], b[MAXN];
map<ll, vector<ll>> mp;
ll ans = 0;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (a[i] < b[i]) {
            ll cnt = (b[i] - a[i] + 29) / 30;
            ans += cnt;
            a[i] += 30 * cnt;
        }
    }

    for (int i = 1; i <= n; i++) {
        mp[b[i]].push_back(a[i]);
    }

    ll lba = 0;
    for (auto& it : mp) {
        vector<ll> arr = it.sc;
        for (auto& i : arr) {
            if (i < lba) {
                ll cnt = (lba - i + 29) / 30;
                ans += cnt;
                i += 30 * cnt;
            }
        }
        for (auto& i : arr) lba = max(lba, i);
    }

    cout << ans;
}