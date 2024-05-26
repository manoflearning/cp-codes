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

int N, M;
int cntC[101010], cntR[101010];
set<int> st;
set<pii> ans;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        int y, x;
        cin >> y >> x;
        cntC[x]++, cntR[y]++;
        ans.insert({ y, x });
    }

    for (int i = 1; i <= N; i++) st.insert(i);

    for (int y = 1; y <= N; y++) {
        vector<int> lazy_del;
        for (auto& x : st) {
            if (ans.count({ y, x })) continue;
            if (cntC[x] == M) {
                lazy_del.push_back(x);
            }
            else {
                cntC[x]++, cntR[y]++;
                ans.insert({ y, x });
                if (cntR[y] == M) break;
            }
        }

        for (auto& x : lazy_del) st.erase(x);
    }

    cout << sz(ans) << '\n';
    for (auto& [y, x] : ans)
        cout << y << ' ' << x << '\n';
}