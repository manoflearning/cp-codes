#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n;
int a[121][121][121];
vector<string> yz, zx, xy, tmp;

void input() {
    cin >> n;
    yz.resize(n);
    zx.resize(n);
    xy.resize(n);
    tmp.resize(n);

    // yz
    for (int z = (n - 1); z >= 0; z--) {
        string s; cin >> s;
        yz[z] = s;
        // for (int y = 0; y < n; y++) {
        //     char c = s[y];
        //     yz[y][z] = c;
        // }
    }
    // zx
    for (int x = n - 1; x >= 0; x--) {
        string s; cin >> s;
        zx[x] = s;
    }
    // xy
    for (int y = n - 1; y >= 0; y--) {
        string s; cin >> s;
        xy[y] = s;
    }
}

bool ans = 1;

void solve() {
    // yz
    for (int y = 0; y < n; y++) {
        for (int z = 0; z < n; z++) {
            if (yz[z][y] != '1') continue;
            for (int x = 0; x < n; x++) {
                a[x][y][z]++;
            }
        }
    }

    // zx
    for (int z = 0; z < n; z++) {
        for (int x = 0; x < n; x++) {
            if (zx[x][z] != '1') continue;
            for (int y = 0; y < n; y++) {
                a[x][y][z]++;
            }
        }
    }

    // xy
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (xy[y][x] != '1') continue;
            for (int z = 0; z < n; z++) {
                a[x][y][z]++;
            }
        }
    }

    // for (int x = 0; x < n; x++) {
    //     for (int y = 0; y < n; y++) {
    //         for (int z = 0; z < n; z++) {
    //             cout << a[x][y][z] << ' ';
    //         }
    //         cout << '\n';
    //     }
    //     cout << '\n';
    // }

    // yz
    for (int y = 0; y < n; y++) {
        for (int z = 0; z < n; z++) {
            bool is_3 = 0;
            for (int x = 0; x < n; x++) {
                if (a[x][y][z] == 3) is_3 = 1;
            }

            if (yz[z][y] == '0' && is_3) ans = 0;
            if (yz[z][y] == '1' && !is_3) ans = 0;
        }
    }
    
    // zx
    for (int z = 0; z < n; z++) {
        for (int x = 0; x < n; x++) {
            bool is_3 = 0;
            for (int y = 0; y < n; y++) {
                if (a[x][y][z] == 3) is_3 = 1;
            }

            if (zx[x][z] == '0' && is_3) ans = 0;
            if (zx[x][z] == '1' && !is_3) ans = 0;
        }
    }

    // xy
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            bool is_3 = 0;
            for (int z = 0; z < n; z++) {
                if (a[x][y][z] == 3) is_3 = 1;
            }

            if (xy[y][x] == '0' && is_3) ans = 0;
            if (xy[y][x] == '1' && !is_3) ans = 0;
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

    input();

    solve();

    cout << (ans ? "Yes" : "No");
}