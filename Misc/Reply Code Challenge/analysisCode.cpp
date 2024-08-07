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

const int MAX = 25 * 1010101;

vector<int> uf(MAX, -1);

int find(int x) {
	if (uf[x] < 0) return x;
	return uf[x] = find(uf[x]);
}

void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	uf[A] += uf[B];
	uf[B] = A;
}

int n, m, k;

struct Snake { int len, idx; };
vector<Snake> snake;
ll lenSum = 0;

ll a[5050][5050];
int w[5050][5050];
ll sum = 0;

vector<ll> arr;

void input() {
    cin >> m >> n >> k;
    snake.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> snake[i].len;
        snake[i].idx = i;
        lenSum += snake[i].len;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            string s; cin >> s;
            if (s == "*") {
                w[i][j] = 1;
                //cout << i << ' ' << j << '\n';
            }
            else {
                a[i][j] = stoi(s);
                arr.push_back(a[i][j]);
                if (a[i][j] > 0) sum++;
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

    cout << lenSum << ' ' << sum << '\n';
}