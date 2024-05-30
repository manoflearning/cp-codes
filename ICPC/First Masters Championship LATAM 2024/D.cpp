#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

int H, M;
int n;
vector<pii> a;
// int lfr, lsc;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> H >> M;
    cin >> n;
    a.resize(n);
    for (auto& i : a) 
        cin >> i.fr >> i.sc;
    
    // sort(a.begin(), a.end(), [&](const pii& p1, const pii& p2) {
    //     return p1.sc < p2.sc;
    // });

    M += 60 * H;

    ll ans = 0;
    for (auto& i : a) {
        ll t = min(M, i.fr);
        M -= t;
        ans += t * i.sc;
    }
    cout << ans;
}