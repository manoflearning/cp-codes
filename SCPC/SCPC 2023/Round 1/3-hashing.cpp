// N <= sum(a[i])인 경우 답은 1.
// 증명 : 모든 i에 대해 a[i] > 0이라면, 그 뒤로 a는 바뀌지 않는다.
// 초기 a에 a[i] = 0인 i가 존재한다면, 모든 a[i] > 0이 될 때까지 쇠구슬이 '퍼진다'.
// 모든 a[i] > 0가 된 시점부터는 a가 바뀌지 않는다.
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 394906913903735329ll;
const ll MOD3 = 4185296581467695669ll;
const int MAXN = 505050;
const int d = 2;

__int128_t dexp1[MAXN], dexp2[MAXN], dexp3[MAXN];
void preprocessing() {
    dexp1[0] = dexp2[0] = dexp3[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        dexp1[i] = d * dexp1[i - 1] % MOD1;
        dexp2[i] = d * dexp2[i - 1] % MOD2;
        dexp3[i] = d * dexp3[i - 1] % MOD3;
    }
}

int n;
vector<ll> a;

void init() {

}

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

void print(const vector<ll>& arr) {
    for (auto& i : arr) cout << i << ' ';
    cout << '\n';
}

int naive() { // O(n^2logn) = O(n^2 + n^2logn)
    map<vector<ll>, int> mp;

    mp[a] = 0;
    for (int t = 1; ; t++) {
        print(a);
        
        vector<ll> tmp = a;
        for (int i = 0; i < n; i++) {
            if (a[i]) tmp[i]--, tmp[(i + 1) % n]++;
        }

        if (mp.count(tmp)) return t - mp[tmp];
        mp[tmp] = t;
        a = tmp;
    }
}

bool isGroup2() {
    for (auto& i : a) 
        if (1 < i) return 0;
    return 1;
}

int getGroup2Ans() {
    __int128_t st1 = 0, st2 = 0, st3 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            st1 = (st1 + a[i] * dexp1[i]) % MOD1;
            st2 = (st2 + a[i] * dexp2[i]) % MOD2;
            st3 = (st3 + a[i] * dexp3[i]) % MOD3;
        }
    }

    __int128_t x1 = st1, x2 = st2, x3 = st3;
    for (int i = 1; i <= n; i++) {
        x1 = (d * (x1 - dexp1[n - 1] * a[n - i]) + a[n - i]) % MOD1;
        x1 = (x1 + MOD1) % MOD1;
        x2 = (d * (x2 - dexp2[n - 1] * a[n - i]) + a[n - i]) % MOD2;
        x2 = (x2 + MOD2) % MOD2;
        x3 = (d * (x3 - dexp3[n - 1] * a[n - i]) + a[n - i]) % MOD3;
        x3 = (x3 + MOD3) % MOD3;
        if (x1 == st1 && x2 == st2 && x3 == st3) return i;
	}
    return -1;
}

ll sumOfAll() {
    ll ret = 0;
    for (auto& i : a) ret += i;
    return ret;
}

void a_few_moment_later() {
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 1; j <= a[i % n] - 1; j++) {
            if (a[(i + j) % n]) {
                int canMove = j;

                a[(i + j) % n] += a[i % n] - j;
                a[i % n] = j;
                break;
            }
        }
    }

    // print(a);

    vector<ll> tmp(n);
    for (int i = 0; i < n; i++) {
        int dist = a[i] - 1;
        while (a[i]--) {
            tmp[(i + dist) % n] = 1;
            dist--;
        }
    }

    a = tmp;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    preprocessing();

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();
        
        input();

        if (n <= 1000 && !isGroup2()) { // 그룹 1 (40점)
            cout << naive() << '\n';
        }
        else if (isGroup2()) { // 그룹 1 (40점) + 그룹 2 (60점)
            cout << getGroup2Ans() << '\n';
        }
        else { // 그룹 3 (100점)
            if (n <= sumOfAll()) cout << 1 << '\n';
            else {
                // 그룹 3를 그룹 2로 환원할 수 있다.
                a_few_moment_later();

                // print(a);

                cout << getGroup2Ans() << '\n';
            }
        }
    }
}