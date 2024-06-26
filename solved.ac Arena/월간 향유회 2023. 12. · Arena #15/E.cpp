// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 3030;

int N;
vector<int> A;
map<int, int> idx;

void input() {
    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        idx[A[i]] = i;
    }
}

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

bool cmp(int p1, int p2) {
    if (gcd(p1, p2) >= 2) return idx[p1] < idx[p2];
    else return p1 < p2;
}

void solve() {
    map<int, int> cnt;
    for (auto& i : A) cnt[i]++;

    for (int x = 0; x < N; x++) {
        for (auto& i : cnt) {
            if (i.sc == 0) continue;

            int now = x;
            while (A[now] != i.fr) now++;

            while (now > x) {
                if (gcd(A[now], A[now - 1]) == 1) {
                    swap(A[now], A[now - 1]);
                    now--;
                }
                else break;
            }

            if (A[x] == i.fr) {
                i.sc--;
                break;
            }
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

    for (auto& i : A) 
        cout << i << ' ';
}