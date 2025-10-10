#pragma GCC optimize("Ofast")
#pragma GCC target("sse,avx2,avx512vl,avx512dq,avx512f")
#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int n, q;
alignas(64) ll x[5050];
alignas(64) ll y[5050];

bool ccw(const ll& p_x, const ll& p_y, 
    const ll& q_x, const ll& q_y, 
    const ll& r_x, const ll& r_y) {
    return (q_x - p_x) * (r_y - p_y) - (r_x - p_x) * (q_y - p_y) > 0;
}

unsigned char ccw(const __m512i& p_x, const __m512i& p_y, 
    const __m512i& q_x, const __m512i& q_y, 
    const __m512i& r_x, const __m512i& r_y) {

    __m512i v1 = _mm512_sub_epi64(q_x, p_x);
    __m512i v2 = _mm512_sub_epi64(r_y, p_y);
    __m512i v3 = _mm512_sub_epi64(r_x, p_x);
    __m512i v4 = _mm512_sub_epi64(q_y, p_y);

    __m512i v5 = _mm512_mullo_epi64(v1, v2);
    __m512i v6 = _mm512_mullo_epi64(v3, v4);
    __m512i v7 = _mm512_sub_epi64(v5, v6);
    __m512i v8 = _mm512_set1_epi64(0);

    return _mm512_cmpgt_epi64_mask(v7, v8);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }

        while (q--) {
            int a, b, c;
            cin >> a >> b >> c;
            a--, b--, c--;

            bool ans = 1;

            __m512i a_x = _mm512_set1_epi64(x[a]);
            __m512i a_y = _mm512_set1_epi64(y[a]);
            __m512i b_x = _mm512_set1_epi64(x[b]);
            __m512i b_y = _mm512_set1_epi64(y[b]);
            __m512i c_x = _mm512_set1_epi64(x[c]);
            __m512i c_y = _mm512_set1_epi64(y[c]);

            for (int i = 0; i + 7 < n; i += 8) {
                __m512i xs = _mm512_loadu_si512((const __m512i *)(x + i));
                __m512i ys = _mm512_loadu_si512((const __m512i *)(y + i));

                unsigned char res1 = ccw(a_x, a_y, b_x, b_y, xs, ys);
                unsigned char res2 = ccw(b_x, b_y, c_x, c_y, xs, ys);
                unsigned char res3 = ccw(c_x, c_y, a_x, a_y, xs, ys);

                unsigned char mask = (res1 & res2 & res3) | (~res1 & ~res2 & ~res3);

                unsigned char skipped = 0;
                if (i <= a && a < i + 8) skipped |= (1 << (a & 7));
                if (i <= b && b < i + 8) skipped |= (1 << (b & 7));
                if (i <= c && c < i + 8) skipped |= (1 << (c & 7));

                ans &= !(mask & ~skipped);
            }

            for (int j = (n - 1) / 8 * 8; j < n; j++) {
                if (j == a || j == b || j == c) continue;
                bool res1 = ccw(x[a], y[a], x[b], y[b], x[j], y[j]);
                bool res2 = ccw(x[b], y[b], x[c], y[c], x[j], y[j]);
                bool res3 = ccw(x[c], y[c], x[a], y[a], x[j], y[j]);
                ans &= !(res1 == res2 && res2 == res3);
            }

            cout << (ans ? "YES" : "NO") << '\n';
        }
    }
}
