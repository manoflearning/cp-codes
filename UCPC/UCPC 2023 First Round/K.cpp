#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

int N;
ll T;
vector<ll> a;

void input() {
    cin >> N >> T;
    a.resize(N);
    for (auto& i : a) cin >> i;
}

bool f(int mid) {
    vector<ll> m;
    for (int i = 0; i < N; i++) {
        ll lb = (i < mid ? 1ll : m[i - mid] + T);
        if (a[i] < lb) return 0;
        m.push_back(max(lb, a[i] - T + 1));
    }
    return 1;
}

int bs() {
    int l = 1, r = N;
    while (l < r) {
        int mid = (l + r) >> 1;
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

    sort(all(a));

    cout << bs();
}