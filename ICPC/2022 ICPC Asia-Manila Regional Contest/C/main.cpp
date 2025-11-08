#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 1'699'741'697;
constexpr int N = 202020;

int n, k;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    a.resize(n);
    for (auto &i : a) cin >> i;

    while (k--) {
        unordered_map<int, int> cnt;
        for (auto &i : a) cnt[i]++;

        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            b[i] = cnt[a[i]];
        }

        if (b == a) break;
        a = b;
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}
