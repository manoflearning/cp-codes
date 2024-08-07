// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 1010;

int n, dep[MAXN];
vector<int> byDep[MAXN];
int now = 0;
pii e[MAXN];

int query1(const vector<int>& a) {
    cout << "? 1 ";
    for (int i = 1; i <= n - 1; i++) 
        cout << a[i] << ' ';
    cout << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int query2(int u, int v) {
    cout << "? 2 " << u << ' ' << v << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    dep[1] = 0;
    byDep[dep[1]].push_back(1);
    for (int v = 2; v <= n - 1; v++) {
        dep[v] = 1 + query2(1, v);
        byDep[dep[v]].push_back(v);
    }

    e[1] = { ++now, ++now };
    for (int d = 1; d <= n; d++) {
        vector<int> a(n, 1);

        int mx1 = 0, mx2 = 0;
        map<int, int> idx, ridx;

        for (auto& i : byDep[d - 1]) {
            idx[i] = i * n;
            ridx[i * n] = i;

            if (idx[mx1] < idx[i]) mx2 = mx1, mx1 = i;
            else if (idx[mx2] < idx[i]) mx2 = i;
            
            a[i] = idx[i];
        }

        
    }
}