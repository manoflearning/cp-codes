#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int B = 29;

int N, K;
vector<ll> a;
ll ans = 0;

void input() {
    cin >> N >> K;
    a.resize(N);
    for (auto& i : a) cin >> i;
}

void solve() {
    vector<ll> rem = a;

    for (int b = B; b >= 0; b--) {
        int cnt = 0;
        vector<ll> tmp;
        for (auto& i : rem) {
            if (i & (1 << b)) {
                cnt++;
                tmp.push_back(i);
            }
        }

        if (cnt >= K) {
            ans |= (1 << b);
            rem = tmp;
        }
    }
}
 
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}