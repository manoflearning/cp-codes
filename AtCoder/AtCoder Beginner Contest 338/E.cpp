// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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

int n;
vector<pii> a, b;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].fr >> a[i].sc;
        if (a[i].fr > a[i].sc) swap(a[i].fr, a[i].sc);
        b.push_back({ a[i].fr, i << 1 });
        b.push_back({ a[i].sc, i << 1 | 1 });
    }

    stack<int> stk;
    sort(all(b));
    for (int i = 0; i < sz(b); i++) {
        if (b[i].sc & 1) {
            if (stk.top() + 1 != b[i].sc) {
                cout << "Yes";
                return 0;
            }
            stk.pop();
        }
        else stk.push(b[i].sc);
    }

    cout << "No";

    // sort(all(a));
    // a.push_back(a.front());

    // bool ans = 1;
    // for (int i = 0; i < n; i++) {
    //     if (i + 1 < n) ans &= (a[i].sc < a[i + 1].fr || a[i + 1].sc < a[i].sc);
    //     else ans &= (a[i + 1].sc < a[i].fr || a[i].sc < a[i + 1].sc);
    // }

    // cout << (ans ? "No" : "Yes");
}