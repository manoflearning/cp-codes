#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 998'244'353;
const int MAXN = 505050;

int n;
int a[MAXN], b[MAXN], rb[MAXN];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        rb[b[i]] = i;
    }
}

ll ans = 1;

void solve(int al, int ar, int bl, int br) {
    // cout << al << ' ' << ar << ' ' << bl << ' ' << br << '\n';

    if (al > ar || bl > br) return;
    if (a[al] != b[br]) { ans = 0; return; }
    if (al == ar) return;
    
    int bidx = rb[a[al + 1]];
    if (bidx + 1 < br) {
        solve(al + 1, al + 1 + (bidx - bl), bl, bidx);
        solve(al + 2 + (bidx - bl), ar, bidx + 1, br - 1);
    }
    else {
        // cout << al << ' ' << ar << ' ' << bl << ' ' << br << '\n';
        ans = ans * 2 % MOD;
        solve(al + 1, ar, bl, br - 1);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve(1, n, 1, n);

    cout << ans;
}