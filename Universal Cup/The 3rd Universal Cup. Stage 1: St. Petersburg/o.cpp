#include <bits/stdc++.h>
using namespace std;
#define ll long long

const double EPS = 1e-7;

int n;
double a, b;
double x1, xn;

double cnt_x1[20], cnt_x2[20];

void input() {
    // double aa, bb;
    // cin >> aa >> bb;

    // a = aa * 100 + EPS;
    // b = bb * 100 + EPS;
    cin >> a >> b;
    cin >> n >> x1 >> xn;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cnt_x1[1] = 1;
    cnt_x1[2] = 0;
    for (int i = 3; i <= n; i++) {
        cnt_x1[i] = a * cnt_x1[i - 1] + b * cnt_x1[i - 2];
    }

    cnt_x2[1] = 0;
    cnt_x2[2] = 1;
    for (int i = 3; i <= n; i++) {
        cnt_x2[i] = a * cnt_x2[i - 1] + b * cnt_x2[i - 2];
    }

    double x2 = (xn - cnt_x1[n] * x1) / cnt_x2[n];

    cout << fixed;
    cout.precision(9);
    for (int i = 1; i <= n; i++) {
        cout << x1 * cnt_x1[i] + x2 * cnt_x2[i] << '\n';
    }
}