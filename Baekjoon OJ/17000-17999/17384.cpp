#include <bits/stdc++.h>
using namespace std;

int n, sz;
string ans;

void f(int l, int r, int cnt, int skipped) {
    int len = r - l + 1;

    if (len == cnt) {
        for (int i = l; i <= r; i++) ans[i] = '#';
        return;
    }
    if (len == 1) return;
    
    int mid = (l + r) >> 1;
    if (!skipped && cnt <= len / 2) {
        f(l, mid, cnt, 1);
    }
    else {
        int lcnt = min(len / 2, cnt - len / 4);
        int rcnt = cnt - lcnt;
        f(l, mid, lcnt, skipped);
        f(mid + 1, r, rcnt, skipped);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (sz = 1; sz < n; sz <<= 1);

    ans.resize(sz, '.');

    f(0, sz - 1, n, 0);

    cout << ans;
}