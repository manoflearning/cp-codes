#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int ANS = 1e9;
const int M = 28;

int N, n;
ll a[121];
int vis[121];

ll comb(int n) {
    int r = n / 2;
    ll ret = 1;
    for (int i = 1; i <= r; i++) {
        ret *= n + 1 - i;
        ret /= i;
    }
    return ret;
}

vector<int> res;

void print() {
    cout << sz(res) << ' ';
    for (auto& i : res) cout << i << ' ';
    exit(0);
}

void naive(int i, ll sum) {
    if (sum == ANS) print();

    if (i == N + 1) return;
    if (sz(res) == M) return;

    if (vis[i]) {
        naive(i + 1, sum);
        return;
    }

    res.push_back(i);
    sum += a[i];
    naive(i + 1, sum);
    res.pop_back();
    sum -= a[i];

    // if ((N - i + 1) + sz(res) > n) {
        naive(i + 1, sum);
    // }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    srand(time(NULL));

    cin >> N;
    n = N / 2;
    for (int i = 1; i <= N; i++) cin >> a[i];

    if (N <= 32) naive(1, 0);
    
    if (N >= M + 2) {
        ll sum = 0;

        for (int i = 0; i < N; i += 2) {
            double goal = (ANS - sum) / (n - i / 2);

            int idx_mn = -1, idx_mx = -1;
            for (int j = 1; j <= N; j++) {
                if (vis[j]) continue;

                if (idx_mn == -1) {
                    idx_mn = idx_mx = j;
                    continue;
                }

                double res = abs(goal - a[j]);
                if (res < abs(goal - a[idx_mn])) idx_mn = j;
                if (res > abs(goal - a[idx_mx])) idx_mx = j;
            }

            vis[idx_mn] = vis[idx_mx] = 1;
            res.push_back(idx_mn);
            sum += a[idx_mn];
        }

        naive(1, sum);
    }
}