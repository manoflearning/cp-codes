#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const double EPS = 1e-7;

int N;
ll R, A, B;
ll X[303030], Y[303030];
int ans = 0;

double theta;
double Xr[303030], Yr[303030];

void input() {
    cin >> N >> R >> A >> B;
    for (int i = 1; i <= N; i++)
        cin >> X[i] >> Y[i];
}

void rotate() {
    theta = atan((double)B / A);
    for (int i = 1; i <= N; i++) {
        Xr[i] = cos(theta) * X[i] + sin(theta) * Y[i];
        Yr[i] = -sin(theta) * X[i] + cos(theta) * Y[i];
    }
}

void solve() {
    vector<pair<double, int>> arr;

    for (int i = 1; i <= N; i++) {
        if (R * R - Yr[i] * Yr[i] < -EPS) continue;
        arr.push_back({ Xr[i] - sqrt(R * R - Yr[i] * Yr[i]), 1 });
        arr.push_back({ Xr[i] + sqrt(R * R - Yr[i] * Yr[i]) + 10*EPS, -1 });
    }

    sort(all(arr));

    int res = 0;
    for (int i = 0; i < sz(arr); i++) {
        res += arr[i].sc;
        if (i + 1 < sz(arr) && arr[i + 1].fr - arr[i].fr < EPS) continue;
        ans = max(ans, res);
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

    rotate();

    solve();

    cout << ans;
}