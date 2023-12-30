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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
int a[55][55];
int A[55], B[55];
int ans = 0;

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int j = 0; j < m; j++) cin >> B[j];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j]) A[i]--, B[j]--;
        }
    }

    vector<int> ordn;
    for (int i = 0; i < n; i++)
        ordn.push_back(i);
    
    srand(time(NULL));
    random_shuffle(all(ordn));

    for (auto& i : ordn) {
        vector<int> ord;
        for (int j = 0; j < m; j++) {
            if (A[i] > 0 && a[i][j] == 0) ord.push_back(j);
            if (A[i] < 0 && a[i][j] == 1) ord.push_back(j);
        }

        // sort(all(ord), [&](int p1, int p2) {
        //     return (A[i] > 0 ? B[p1] > B[p2] : B[p1] < B[p2]);
        // });

        if (A[i] > 0) {
            for (auto& j : ord) {
                a[i][j] = 1;
                A[i]--, B[j]--;
                ans++;
                if (A[i] == 0) break;
            }
        }
        if (A[i] < 0) {
            for (auto& j : ord) {
                a[i][j] = 0;
                A[i]++, B[j]++;
                ans++;
                if (A[i] == 0) break;
            }
        }
    }

    for (int i = 0; i < n; i++)
        if (A[i] != 0) { cout << -1; return 0; }
    for (int i = 0; i < m; i++)
        if (B[i] != 0) { cout << -1; return 0; }

    cout << ans;
}