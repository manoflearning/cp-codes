#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Point {
    ll x, y;
};

int n;
vector<Point> a;
vector<ll> xx, yy;
int ans[55];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.y >> i.x;
        yy.push_back(i.y); 
        xx.push_back(i.x);
    }

    for (int i = 0; i < 55; i++) ans[i] = 1e9 + 7;

    for (int i = 0; i < sz(yy); i++) {
        for (int j = 0; j < sz(xx); j++) {
            int y = yy[i], x = xx[j];
            
            sort(a.begin(), a.end(), [&](const Point& lhs, const Point& rhs) {
                return abs(lhs.y - y) + abs(lhs.x - x) < abs(rhs.y - y) + abs(rhs.x - x);
            });

            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += abs(a[i].y - y) + abs(a[i].x - x);
                ans[i + 1] = min(ans[i + 1], sum);
            }
        }
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';

    return 0;
}