#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int n;
string s;

int psum[32323][2];

vector<pii> ans;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'H') {
            psum[i][0] = 3 + (i > 0 ? psum[i - 1][0] : 0);
            psum[i][1] = 3 + (i > 0 ? psum[i - 1][1] : 0);
        }
        if (s[i] == 'T') {
            if (i & 1) {
                psum[i][0] = 5 + (i > 0 ? psum[i - 1][0] : 0);
                psum[i][1] = 1 + (i > 0 ? psum[i - 1][1] : 0);
            }
            else {
                psum[i][0] = 1 + (i > 0 ? psum[i - 1][0] : 0);
                psum[i][1] = 5 + (i > 0 ? psum[i - 1][1] : 0);
            }
        }
    }

    for (int x = 1; x <= 5 * n; x++) {
        int y = 0;

        int acc = 0;

        int prv = -1;
        while (prv < n - 1) {
            bool bit = (prv == -1 ? 1 : (prv & 1));

            int l = prv + 1, r = n - 1;
            while (l < r) {
                int mid = (l + r) >> 1;

                int res = psum[mid][bit] - (prv >= 0 ? psum[prv][bit] : 0);
                if (res >= x) r = mid;
                else l = mid + 1;
            }
            acc += psum[l][bit] - (prv >= 0 ? psum[prv][bit] : 0);
            if (acc >= x) acc = 0, y++;
            prv = l;
        }

        if (y == 0) break;

        if (acc == 0)
            ans.push_back({ x, y });
    }

    cout << sz(ans) << '\n';
    for (auto& i : ans)
        cout << i.fr << ' ' << i.sc << '\n';
}
