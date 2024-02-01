// if n = 1
// a, b, ..., a + k - 1 -> k
// if n = 2
// aa, ab, ac, ..., ba, ..., -> k * k
// if n = t -> k^t

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

int power[27][27];

void preprocessing() {
    for (int j = 1; j <= 26; j++) power[j][0] = 1;

    for (int i = 1; i <= 26; i++) {
        for (int j = 1; j <= 26; j++) {
            power[j][i] = j * power[j][i - 1];
        }
    }
}

int n, k, m;
string s, ans, du;
int cnt[26];
vector<int> psum[26];

void init() {
    memset(cnt, 0, sizeof(cnt));
    ans.clear();
    du.clear();
}

void input() {
    cin >> n >> k >> m;
    cin >> s;
}

bool isExist(const string& t) {
    int now = 0;
    for (auto& c : s) {
        if (now < sz(t) && c == t[now]) now++;
    }
    return now == sz(t);
}

void bf(int x) {
    if (!ans.empty()) return;
    if (sz(du) == n - 1 || x >= INF) { 
        for (int i = 0; i < k; i++)
            if (x >= INF || (x < m && psum[i][x] == INF)) { 
                while (sz(du) < n) du.push_back(i + 'a'); 
                break;
            }
        if (sz(du) == n) ans = du;
        return;
    }
    else {
        for (int i = 0; i < k; i++) {
            du.push_back(i + 'a');
            bf(psum[i][x] + 1);
            du.pop_back();
        }
    }
}

void randomSol() {
    srand(time(NULL));
    
    for (int i = 0; i < 3; i++) {
        string tmp;
        while (sz(tmp) < n) {
            tmp.push_back(rand() % k + 'a');
        }

        int perCnt = 0;
        do {
            if (!isExist(tmp)) { ans = tmp; break; }
            perCnt++;
            if (perCnt == 100) break;
        } while (next_permutation(all(tmp)));
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        for (int i = 0; i < 26; i++) {
            psum[i].clear();
            psum[i].resize(m, INF);
        }
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < k; j++) {
                if (i + 1 < m) psum[j][i] = psum[j][i + 1];
            }
            psum[s[i] - 'a'][i] = i;
        }

        for (auto& c : s) cnt[c - 'a']++;
        
        for (int i = 0; i < k; i++) {
            if (cnt[i] >= n) continue;
            while (sz(ans) < n) ans.push_back(i + 'a');
            break;
        }

        if (!ans.empty()) {
            cout << "NO\n";
            cout << ans << '\n';
            continue;
        }
        
        // if (power[k][n] <= 300) bf(0);
        // else randomSol();
        bf(0);

        cout << (ans.empty() ? "YES" : "NO") << '\n';
        if (!ans.empty()) cout << ans << '\n';
    }
}