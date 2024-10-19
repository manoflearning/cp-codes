#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, q;

bool is_contain(int x, int y, int z) {
    if (x <= z) return x <= y && y <= z;
    else return x <= y || y <= z;
}

ll cal(int x, int y) {
    if (x <= y) return y - x;
    else return n - x + y;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;

    ll ans = 0;
    int loc1 = 0, loc2 = 1;
    while (q--) {
        char h; int t;
        cin >> h >> t;
        t--;
        if (h == 'L') {
            if (is_contain(loc1, loc2, t)) ans += cal(t, loc1);
            else ans += cal(loc1, t);
            loc1 = t;
        }
        if (h == 'R') {
            if (is_contain(loc2, loc1, t)) ans += cal(t, loc2);
            else ans += cal(loc2, t);
            loc2 = t;
        }
    }

    cout << ans;
}
