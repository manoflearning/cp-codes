// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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

int n; // <= 30
string s;
string ans;

void input() { cin >> n >> s; }

// t0 = A
// if t1 = B -> 00..0
// if t1 = A -> 11..0

void solve() {
    vector<pii> range;

    int l = -1, r = -1;
    s.push_back('0');
    for (int i = 0; i < sz(s); i++) {
        if (s[i] == '1') {
            if (l == -1 && r == -1) l = r = i;
            else r = i;
        }
        if (s[i] == '0') {
            if (l == -1 && r == -1) continue;
            else {
                range.push_back({ l, r });
                l = r = -1;
            }
        }
    }

    reverse(all(range));

    for (auto& i : range) {
        for (int j = 0; j < i.sc + 1; j++) ans.push_back('A');
        for (int j = 0; j < i.fr; j++) ans.push_back('B');
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

    solve();

    cout << sz(ans) << '\n';
    cout << ans;
}