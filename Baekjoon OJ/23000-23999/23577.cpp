#pragma gcc optimize ("O3")
#pragma gcc target ("avx2")

#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;
#define ll long long

const int MAXN = 2020;

int N;
string A[MAXN];
short C[MAXN][MAXN] __attribute__ ((aligned (64)));

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
}

void getC() { // O(N^2)
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            short res = 0;
            for (int k = 0; k < 4; k++) {
                res *= 10;
                if (A[i][k] == A[j][k]) res += A[i][k] - '0';
            }
            C[i][j] = C[j][i] = res;
        }
    }
}

ll solve() { // O(N^3 / 6 / 16)
    ll ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            __m256i Cij = _mm256_set1_epi16(C[i][j]);
            
            __m256i acc = _mm256_setzero_si256();
            for (int k = j + 1; k < N; k += 16) {
                if (k + 16 <= N) {
                    __m256i Cik = _mm256_set1_epi16(C[i][k]);
                    __m256i Cjk = _mm256_set1_epi16(C[j][k]);
                    __m256i cmp1 = _mm256_cmpeq_epi16(Cik, Cij);
                    __m256i cmp2 = _mm256_cmpeq_epi16(Cjk, Cij);

                    __m256i res = _mm256_and_si256(cmp1, cmp2);
                    acc = _mm256_sub_epi16(acc, res);
                } else {
                    for (int kk = k; kk < N; kk++) {
                        if (C[i][j] == C[i][k] && C[i][j] == C[j][k]) ret++;
                    }
                }
            }

            short tmp[16];
            _mm256_store_si256((__m256i*)tmp, acc);
            for (int k = 0; k < 16; k++)
                ret += tmp[k];
        }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getC();

    ll ans = solve();
    cout << ans;
}