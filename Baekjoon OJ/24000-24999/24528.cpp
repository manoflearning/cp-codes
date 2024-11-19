#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 303030, MAXQ = 303030;

int n, m, q;
int a[MAXN], x[MAXQ];

void input() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) cin >> x[i];
}

bool f(ll mid) {
    // base case
    queue<int> qu;
    qu.push(0);

    // inductive step
    int s1 = 1;
    for (int e = m; e <= n; e++) {
        while (a[e] - a[s1] > mid) s1++;
        int s2 = e - m + 1;

        while (!qu.empty() && qu.front() < s1 - 1) qu.pop();
        if (!qu.empty() && qu.front() < s2) {
            qu.push(e);
            if (e == n) return 1;
        }
    }
    return 0;
}

ll bt() {
    ll l = 0, r = 1e9;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (f(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    ll lb = bt();
    for (int i = 1; i <= q; i++) {
        cout << (lb <= x[i] ? 1 : 0);
    }
}
