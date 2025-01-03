#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, -1, 1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct Node {
    int y, x, d;
};

int n, k;
int arr[15][15];
vector<int> vi[15][15];
vector<Node> a;

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> arr[i][j];
        }
    }
    
    a.resize(k);
    for (int i = 0; i < k; i++) {
        auto& it = a[i];
        cin >> it.y >> it.x >> it.d;
        it.d--;
        vi[it.y][it.x].push_back(i);
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    for (int res = 1; res <= 1000; res++) {
        for (int i = 0; i < k; i++) {
            auto& it = a[i];
            if (vi[it.y][it.x].front() != i) continue;
            //if (res == 1) cout << i + 1 << ' ' << it.d << '\n';
            int ny = it.y + dy[it.d], nx = it.x + dx[it.d];
            if (ny < 1 || n < ny || nx < 1 || n < nx || arr[ny][nx] == 2) {
                it.d = (it.d ^ 1);

                //for (auto& j : vi[it.y][it.x]) a[j].d = nd;

                ny = it.y + dy[it.d], nx = it.x + dx[it.d];
                if (ny < 1 || n < ny || nx < 1 || n < nx || arr[ny][nx] == 2) continue;
            }

            if (arr[ny][nx] == 1) {
                swap(vi[it.y][it.x].front(), vi[it.y][it.x].back());
            }

            vector<int> tmp = vi[it.y][it.x];
            vi[it.y][it.x].clear();
            for (auto& i : tmp) {
                vi[ny][nx].push_back(i);
                a[vi[ny][nx].back()].y = ny;
                a[vi[ny][nx].back()].x = nx;
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (sz(vi[i][j]) >= 4) {
                    cout << res;
                    return 0;
                }
            }
        }

        /*if (res == 2) {
            for (int i = 0; i < k; i++) {
                cout << i + 1 << ' ' << a[i].y << ' ' << a[i].x << ' ' << a[i].d << '\n';
            }
        }*/
    }

    cout << -1;
}