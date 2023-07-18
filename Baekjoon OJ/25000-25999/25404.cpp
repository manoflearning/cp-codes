#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n, a[101010];
vector<int> idx[101010];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
}

void comp() {
    vector<int> c(1, -1);
    for (int i = 0; i < n; i++)
        c.push_back(a[i]);

    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    for (int i = 0; i < n; i++)
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
}

ll sd(int st, int en) { return min(abs(st - en), n - abs(st - en)); }
ll ld(int st, int en) { return max(abs(st - en), n - abs(st - en)); }

map<int, ll> dp[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    comp();

    for (int i = 0; i < n; i++)
        idx[a[i]].push_back(i);

    // base case
    if (sz(idx[1]) == 1) {
        dp[1][idx[1][0]] = sd(0, idx[1][0]);
    }
    else {
        
    }
}