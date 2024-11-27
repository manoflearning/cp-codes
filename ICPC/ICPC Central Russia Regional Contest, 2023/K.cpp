#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const double PI = 3.14159265358979323846264338327950288;
const int DIV = 10'000'000;

ll a, b, c, d;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> a >> b >> c >> d;
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);

    if (c <= a && d <= b) {
        cout << "YES";
        exit(0);
    }

    for (double theta = PI / 2 / DIV; theta < PI / 2; theta += PI / 2 / DIV) {
        double res1 = c * sin(theta) + d * cos(theta);
        double res2 = c * cos(theta) + d * sin(theta);
        if (res1 <= b && res2 <= a) {
            cout << "YES";
            exit(0);
        }
    }

    cout << "NO";
}
