#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const string sky = "sky", building = "building";

string query(int x, ll y) {
    cout << "? " << x << ' ' << y << '\n';
    cout << flush;
    string ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int w; ll h;
    cin >> w >> h;

    vector<int> ord(w), vis(w + 1);
    iota(all(ord), 1);

    srand(time(NULL));
    shuffle(all(ord), default_random_engine(rand()));

    int optx = 1;
    ll opty = 0;
    for (auto& x : ord) {
        if (opty < h && query(x, opty + 1) == building) {
            ll l = opty + 1, r = h;
            while (l < r) {
                ll mid = (l + r + 1) >> 1;
                if (query(x, mid) == building) l = mid;
                else r = mid - 1;
            }
            optx = x, opty = l;
        }
    }

    cout << "! " << optx << ' ' << opty;
}