#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;

int n, k;
int a[N];

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

bool f(double x) {
    vector<double> psum(n + 1);
    for (int i = 1; i <= n; i++) {
        psum[i] = a[i] - x + psum[i - 1];
    }

    if (psum[n] < 0) return 0;

    vector<double> lis;
    lis.push_back(psum[0]);

    for (int i = 1; i <= n; i++) {
        if (psum[i] < 0) continue;

        if (lis.back() <= psum[i]) {
            lis.push_back(psum[i]);
            if (i == n) return sz(lis) >= k + 1;
        }
        else {
            int l = 1, r = sz(lis) - 1;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (lis[mid] <= psum[i]) l = mid + 1;
                else r = mid;
            }
            lis[l] = psum[i];

            if (i == n) return l >= k;
        }
    }

    return 0;
}

double ans;
void bs() {
    double l = 1.0, r = 1000.0;
    for (int tt = 0; tt < 50; tt++) {
        double mid = (l + r) / 2;
        if (f(mid)) l = mid;
        else r = mid;
    }
    ans = l;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    bs();

    cout << fixed;
    cout.precision(8);
    cout << ans;
}