#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int p, q;
    cin >> p >> q;

    int x, y;
    cin >> x >> y;

    if (p <= x && x < p + 100 && q <= y && y < q + 100) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}