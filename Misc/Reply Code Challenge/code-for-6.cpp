//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m, k;

struct Snake { int len, idx; };
vector<Snake> snake;

ll a[5050][5050];
int w[5050][5050];
int posCnt = 0;

int sty = -1, stx = -1;
queue<pii> portal;

void input() {
    cin >> m >> n >> k;
    snake.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> snake[i].len;
        snake[i].idx = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            string s; cin >> s;
            if (s == "*") w[i][j] = 1;
            else {
                a[i][j] = stoi(s);
                if (a[i][j] > 0) posCnt++;
            }
        }
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
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            if (w[i][j] && a[i][j + 1] > 0) portal.push({ i, j });
            if (sty == -1 && a[i][j] > 0) sty = i, stx = j;
        }
    }

    int nowy = sty, nowx = stx + 1;
    int sidx = 0;
    while (posCnt >= snake[sidx].len) {
        assert(!w[nowy][nowx]);
        assert(a[nowy][nowx] > 0);

        cout << nowx - 1 << ' ' << nowy - 1 << ' ';
        snake[sidx].len--;
        posCnt--;
        nowx++;

        while (snake[sidx].len > 0) {
            assert(a[nowy][nowx] >= 0);
            if (w[nowy][nowx]) {
                nowy = portal.front().fr;
                nowx = portal.front().sc;
                portal.pop();

                cout << nowx - 1 << ' ' << nowy - 1 << ' ';
                assert(snake[sidx].len  - 1 > 0);
            }
            else cout << "R ";
            nowx++;
            snake[sidx].len--;
            posCnt--;
        }

        sidx++;
        cout << '\n';
    }
    for (int i = sidx; i < k; i++) cout << '\n';
}