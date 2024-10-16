#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n, l, r, k;
    cin >> n >> l >> r >> k;
    
    vector<ll> a(n);
    for (auto& i : a) cin >> i;

    int inCnt = 0, deCnt = 0;
    for (int i = 0; i + 1 < n; i++) {
        if (a[i] < a[i + 1]) inCnt++;
        if (a[i] > a[i + 1]) deCnt++;
    }

    if (inCnt - k * deCnt > r - l) {
        cout << -1;
        return 0;
    }
    if (deCnt - k * inCnt > r - l) {
        cout << -1;
        return 0;
    }

    vector<int> ans;
    ans.push_back(r - inCnt);
    for (int i = 0; i + 1 < n; i++) {
        if (a[i] < a[i + 1]) {
            inCnt--;
            ans.push_back(ans.back() + 1);
        }
        if (a[i] > a[i + 1]) {
            deCnt--;
            ans.push_back(ans.back() - min<ll>(k, inCnt));
        }
        if (a[i] == a[i + 1]) ans.push_back(ans.back());
    }

    for (auto& i : ans)
        cout << i << ' ';
}