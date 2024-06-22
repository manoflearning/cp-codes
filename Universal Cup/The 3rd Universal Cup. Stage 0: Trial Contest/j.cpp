#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 101010;

int n;
ll p, c[N];
__int128_t psum[N];
vector<int> fa;

void input() {
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        psum[i] = c[i] + psum[i - 1];
    }
}

void get_first_appear() {
    set<ll> vis;
    for (int i = 1; i <= n; i++) {
        if (!vis.count(c[i])) {
            vis.insert(c[i]);
            fa.push_back(i);
        }
    }
}

void solve() {
    for (auto& i : fa) {
        __int128_t x = c[i];

        __int128_t rem = p - ((x - 1) * (i - 1) + psum[i - 1]);
        if (rem < x) {
            cout << i - 1;
            exit(0);
        }
    }
    cout << n;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    
    get_first_appear();

    solve();
}