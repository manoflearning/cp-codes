#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int H = 2020;
constexpr int W = 2020;

struct hashint {
    static constexpr int MOD1 = 1e9 + 7;
    static constexpr int MOD2 = 1e9 + 9;

    ll v1, v2;
    
    hashint() : v1{}, v2{} {}
    hashint(ll v) : v1{v % MOD1}, v2{v % MOD2} {}

    hashint operator+(const hashint &rhs) const {
        hashint ret{};
        ret.v1 = v1 + rhs.v1;
        ret.v1 -= (ret.v1 >= MOD1) * MOD1;
        ret.v2 = v2 + rhs.v2;
        ret.v2 -= (ret.v2 >= MOD2) * MOD2;
        return ret;
    }
    hashint operator-(const hashint &rhs) const {
        hashint ret{};
        ret.v1 = v1 - rhs.v1;
        ret.v1 += (ret.v1 < 0) * MOD1;
        ret.v2 = v2 - rhs.v2;
        ret.v2 += (ret.v2 < 0) * MOD2;
        return ret;
    }
    hashint operator*(const hashint &rhs) const {
        hashint ret{};
        ret.v1 = (v1 * rhs.v1) % MOD1;
        ret.v2 = (v2 * rhs.v2) % MOD2;
        return ret;
    }
    bool operator==(const hashint &rhs) const {
        return v1 == rhs.v1 && v2 == rhs.v2;
    }
};

int hp, wp, hm, wm;
vector<vector<bool>> a, b;

hashint pow2[H * W]{};
hashint hash_a{};
hashint psum_1d[H][W]{};
hashint psum_2d[H][W]{};

int ans = 0;

void preprocess() {
    pow2[0] = hashint{1};
    for (int i = 1; i < H * W; i++)
        pow2[i] = pow2[i - 1] * 2;
}

void input() {
    cin >> hp >> wp >> hm >> wm;
    a.resize(hp, vector<bool>(wp));
    for (int i = 0; i < hp; i++) {
        string s; cin >> s;
        for (int j = 0; j < wp; j++) {
            a[i][j] = (s[j] == 'o' ? 1 : 0);
        }
    }
    b.resize(hm, vector<bool>(wm));
    for (int i = 0; i < hm; i++) {
        string s; cin >> s;
        for (int j = 0; j < wm; j++) {
            b[i][j] = (s[j] == 'o' ? 1 : 0);
        }
    }
}

void solve() {
    for (int i = 0; i < hp; i++) {
        hashint row{};
        for (int j = 0; j < wp; j++)
            row = row * pow2[1] + hashint{a[i][j]};
        hash_a = hash_a * pow2[wp] + row;
    }
    for (int i = 0; i < hm; i++) {
        psum_1d[i][0] = hashint{b[i][0]};
        for (int j = 1; j < wm; j++) {
            psum_1d[i][j] = psum_1d[i][j - 1] * pow2[1] + hashint{b[i][j]};
            // cout << i << ' ' << j << ' ' << psum_1d[i][j].v1 << '\n';
        }
    }

    for (int i = 0; i < hm; i++) {
        for (int j = wp - 1; j < wm; j++) {
            psum_2d[i][j] = (i >= 1 ? psum_2d[i - 1][j] * pow2[wp] : 0) + (psum_1d[i][j] - (j >= wp ? psum_1d[i][j - wp] * pow2[wp] : 0));

            if (i >= hp - 1) {
                hashint hash_b = psum_2d[i][j] - (i >= hp ? psum_2d[i - hp][j] * pow2[hp * wp] : 0);
                if (hash_a == hash_b) {
                    // cout << i << ' ' << j << ' ' << hash_b.v1 << ' ' << hash_b.v2 << '\n';
                    ans++;
                }
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    preprocess();

    input();

    solve();

    cout << ans;
}