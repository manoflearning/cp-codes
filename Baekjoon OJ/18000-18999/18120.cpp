#include <bits/stdc++.h>
using namespace std;
#define ll long long

const double EPS = 1e-7;

int N;
ll A;
struct Node { ll x, y, w; };
vector<Node> arr;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> A;
    arr.resize(N);
    for (auto& i : arr)
        cin >> i.x >> i.y >> i.w;

    sort(arr.begin(), arr.end(), [&](const Node& p1, const Node& p2) {
        return p1.x * p1.x + p1.y * p1.y < p2.x * p2.x + p2.y * p2.y;
    });

    double ans = 0;

    double prvSum = 0;
    ll sum = 0;
    vector<Node> cur;
    for (int i = 0; i < N; i++) {
        double mnR = sqrt(arr[i].x * arr[i].x + arr[i].y * arr[i].y);
        double mxR = (i == N - 1 ? 1e9 : sqrt(arr[i + 1].x * arr[i + 1].x + arr[i + 1].y * arr[i + 1].y));

        if (i > 0) {
            double prv = sqrt(arr[i - 1].x * arr[i - 1].x + arr[i - 1].y * arr[i - 1].y);
            prvSum += sum * (mnR - prv);
        }
        sum += arr[i].w;

        // extreme value of a quadratic function
        double x = (double)sum / (2 * A);
        double res = -A * x * x + sum * (x - mnR) + prvSum;
        ans = max(ans, res);

        // ternary search
        /*double l = mnR, r = mxR;
        while (r - l > EPS) {
            double mid1 = (2 * l + r) / 3;
            double mid2 = (l + 2 * r) / 3;
            double val1 = sum * (mid1 - mnR) - A * mid1 * mid1;
            double val2 = sum * (mid2 - mnR) - A * mid2 * mid2;
            if (val1 < val2) l = mid1;
            else r = mid2;
        }

        double res2 = prvSum + sum * (l - mnR) - A * l * l;
        ans = max(ans, res2);*/
    }

    cout << fixed;
    cout.precision(6);
    cout << ans;
}