#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

// array<int, 20202020> arr;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    ll a1, k, p;
    cin >> n >> a1 >> k >> p;

    // arr[1] = a1;
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(a1);
    ll y = a1;
    for (int i = 2; i <= n; i++) {
        ll x = y * k % p;
        pq.push(x);
        y = x;
        if (sz(pq) > 5) pq.pop();
    }

    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
}
