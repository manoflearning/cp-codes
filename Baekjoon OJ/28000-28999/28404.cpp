#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX_FI = 86;
const ll MX = 1e18;

ll fi[MAX_FI + 1];

bool isF

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // initialize
    fi[1] = 1, fi[2] = 2;
    for (int i = 3; i <= MAX_FI; i++) {
        fi[i] = fi[i - 1] + fi[i - 2];
    }

    map<ll, ll> a;
    a[1] = 1, a[2] = 2, a[3] = 3;
    a[4] = 6;
    ll idx1 = 6, idx2 = 4;
    while (idx1 <= MX && idx2 <= MAX_FI) {
        a[idx1] = fi[idx2];
        idx2 = idx1;
        idx1 = a[idx1];
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= MAX_FAC; i++) {
        if (!a.count(i)) pq.push(i);
    }

    for (int i = 1; i <= MAX_FAC; i++) {
        if (a.count(i)) continue;
        for (int j = i + 1; j <= MAX_FAC; j++) {
            if (a.count(j)) continue;
            ll idx2 = i;
            ll idx1 = j;
            a[idx2] = idx1;
            while (idx1 <= MX && idx2 <= MAX_FAC) {
                a[idx1] = fi[idx2];
                idx2 = idx1;
                idx1 = a[idx1];
            }
            break;
        }
    }

    // for (auto& i : a) {
    //     cout << i.first << ' ' << i.second << '\n';
    // }
    
    // solve
    int tc; cin >> tc;
    while (tc--) {
        ll n; cin >> n;
        if (a.count(n)) cout << a[n] << '\n';
        else cout << -1 << '\n';
    }
}