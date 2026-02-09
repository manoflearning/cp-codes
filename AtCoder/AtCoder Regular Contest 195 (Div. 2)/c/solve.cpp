#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int X = 1'000'000;
constexpr int Y = 1'000'000;

struct Node {
    char c; int x, y;            
};

void update(vector<Node> &ans, int &x, int &y, const char c, const int dx, const int dy, const int siz) {
    const int base = sz(ans);
    while (sz(ans) < base + siz) {
        x += dx, y += dy;
        ans.push_back({c, x, y});
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int r, b;
        cin >> r >> b;

        if (r & 1) {
            cout << "No\n";
            continue;
        }
        if (r == 0 && (b & 1)) {
            cout << "No\n";
            continue;
        }

        vector<Node> ans;

        if (r > 0) {
            const int p = r / 2;

            int x = X, y = Y;
            ans.push_back({'R', x, y});
            update(ans, x, y, 'R', -1, 0, p - 1);
            if (b > 0 && (~b & 1)) ans.push_back({'B', x - 1, y});
            y--;
            ans.push_back({'R', x, y});
            update(ans, x, y, 'R', +1, 0, p - 1);

            if (b) {
                const int q = (b + 1) / 2 - 1;

                if (q + 1 > 0) {
                    x++;
                    ans.push_back({'B', x, y});
                    update(ans, x, y, 'B', +1, +1, q);
                }
                
                if (q > 0) {
                    x--, y++;
                    ans.push_back({'B', x, y});
                    update(ans, x, y, 'B', -1, -1, q - 1);
                }
            }
            
        } else {
            const int q = b / 2;

            int x = X, y = Y;
            ans.push_back({'B', x, y});
            update(ans, x, y, 'B', +1, +1, q - 1);
            x--, y++;
            ans.push_back({'B', x, y});
            update(ans, x, y, 'B', -1, -1, q - 1);
        }

        cout << "Yes\n";
        for (const auto &i : ans) {
            cout << i.c << ' ' << i.x << ' ' << i.y << '\n';
        }
    }

    return 0;
}
