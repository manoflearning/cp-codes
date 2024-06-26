#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 20'070'713;
const int MAXN = 101010;

int n;
vector<pii> a;
ll dp[MAXN];

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i.fr >> i.sc;
}

void bottom_up() {
    // base case
    dp[0] = 2;
    // inductive step
    for (int i = 1; i < sz(a); i++) {
        int l = 0, r = i - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[i].fr <= a[mid].sc) r = mid - 1;
            else l = mid;
        }
        dp[i] = (dp[i - 1] + (a[l].sc < a[i].fr ? dp[l] : 1)) % MOD;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(all(a), [&](const pii& lhs, const pii& rhs) {
        return lhs.sc < rhs.sc;
    });

    bottom_up();

    cout << dp[sz(a) - 1];
}