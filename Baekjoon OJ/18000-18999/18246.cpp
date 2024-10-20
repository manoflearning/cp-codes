#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n, m;
int psum[1515][1515];

int flag;
struct Seg2D {
    vector<vector<int>> t;
    void build() {
        for (flag = 1; flag < 1515; flag <<= 1);
        t.resize(2 * flag, vector<int>(2 * flag));
        for (int i = 1; i < 1515; i++) {
            for (int j = 1; j < 1515; j++) {
                t[i + flag - 1][j + flag - 1] = psum[i][j];
            }
        }

        for (int i = flag; i < 2 * flag; i++) {
            for (int j = flag - 1; j >= 1; j--) {
                t[i][j] = max(t[i][j << 1], t[i][j << 1 | 1]);
            }
        }

        for (int i = flag - 1; i >= 1; i--) {
            for (int j = 1; j < 2 * flag; j++) {
                t[i][j] = max(t[i << 1][j], t[i << 1 | 1][j]);
            }
        }
    }
    int query2(int s2, int e2, int n1, int n2 = 1, int nl2 = 1, int nr2 = flag) {
        if (nr2 < s2 || e2 < nl2) return 0;
        if (s2 <= nl2 && nr2 <= e2) return t[n1][n2];
        int mid2 = (nl2 + nr2) >> 1;
        return max(query2(s2, e2, n1, n2 << 1, nl2, mid2),
        query2(s2, e2, n1, n2 << 1 | 1, mid2 + 1, nr2));
    }
    int query1(int s1, int e1, int s2, int e2, int n1 = 1, int nl1 = 1, int nr1 = flag) {
        if (e1 < nl1 || nr1 < s1) return 0;
        if (s1 <= nl1 && nr1 <= e1) return query2(s2, e2, n1);
        int mid1 = (nl1 + nr1) >> 1;
        return max(query1(s1, e1, s2, e2, n1 << 1, nl1, mid1),
        query1(s1, e1, s2, e2, n1 << 1 | 1, mid1 + 1, nr1));
    }
}seg;

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        y1++, x1++, y2++, x2++;
        psum[y1][x1]++;
        psum[y2][x1]--;
        psum[y1][x2]--;
        psum[y2][x2]++;
    }
}

void build_psum() {
    for (int i = 1; i < 1515; i++) {
        psum[0][i] += psum[0][i - 1];
        psum[i][0] += psum[i - 1][0];
    }
    for (int i = 1; i < 1515; i++) {
        for (int j = 1; j < 1515; j++) {
            psum[i][j] += psum[i][j - 1];
            psum[i][j] += psum[i - 1][j];
            psum[i][j] -= psum[i - 1][j - 1];
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    build_psum();

    seg.build();

    for (int i = 0; i < m; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        y1++, x1++, y2++, x2++;
        cout << seg.query1(y1, y2 - 1, x1, x2 - 1) << '\n';

        // for (int y = y1; y < y2; y++) {
        //     for (int x = x1; x < x2; x++) {
        //         cout << psum[y][x] << ' ';
        //     }
        //     cout << '\n';
        // }
    }
}