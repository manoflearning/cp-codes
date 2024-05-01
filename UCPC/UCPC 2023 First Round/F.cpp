#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

int N, Q;
vector<pair<int, int>> arr = { { 1, 1 }, { 1, 2 }, { 2, 1 }, { 2, 2 } };
vector<pair<int, int>> mov = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
vector<pair<int, int>> sw;

int ans[1010][1010];
map<int, pair<int, int>> loc;

int idx(int y, int x) {
    for (int i = 0; i < 4; i++) {
        if (arr[i].fr % 2 == y % 2 && arr[i].sc % 2 == x % 2) {
            y -= mov[i].fr, x -= mov[i].sc;
            if (y <= 0) y = ((y - 1) % N + N) % N + 1;
            if (x <= 0) x = ((x - 1) % N + N) % N + 1;
            return (y - 1) * N + x;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> Q;
    while (Q--) {
        string op; cin >> op;
        if (op == "RO") {
            for (int i = 0; i < 4; i++) {
                if (arr[i].fr % 2 == 1) arr[i].sc++, mov[i].sc++;
            }
        }
        if (op == "RE") {
            for (int i = 0; i < 4; i++) {
                if (arr[i].fr % 2 == 0) arr[i].sc++, mov[i].sc++;
            }
        }
        if (op == "CO") {
            for (int i = 0; i < 4; i++) {
                if (arr[i].sc % 2 == 1) arr[i].fr++, mov[i].fr++;
            }
        }
        if (op == "CE") {
            for (int i = 0; i < 4; i++) {
                if (arr[i].sc % 2 == 0) arr[i].fr++, mov[i].fr++;
            }
        }
        if (op == "S") {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            sw.push_back({ idx(y1, x1), idx(y2, x2) });
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int x = idx(i, j);
            ans[i][j] = x;
            loc[x] = { i, j };
        }
    }

    reverse(all(sw));

    for (auto& i : sw) {
        auto [y1, x1] = loc[i.fr];
        auto [y2, x2] = loc[i.sc];
        
        swap(ans[y1][x1], ans[y2][x2]);

        loc[i.fr] = { y2, x2 };
        loc[i.sc] = { y1, x1 };
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}