#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n, p, q, r;
string a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> p >> q >> r;
    cin >> a;

    int cntS = 0, cntK = 0, cntH = 0;
    int cntSK = 0, cntSH = 0, cntKH = 0;
    int cntSKH = 0;

    int i = 0;
    while (i < n) {
        if (a[i] == 'S') {
            if (i + 1 < n) {
                if (a[i + 1] == 'S') {
                    cntS++; i++;
                }
                else if (a[i + 1] == 'K') {
                    if (i + 2 < n && a[i + 2] == 'H') {
                        cntSKH++; i += 3;
                    }
                    else { cntSK++; i += 2; }
                }
                else if (a[i + 1] == 'H') {
                    cntSH++; i += 2;
                }
                else assert(0);
            }
            else { cntS++; i++; }
        }
        else if (a[i] == 'K') {
            if (i + 1 < n) {
                if (a[i + 1] == 'S' || a[i + 1] == 'K') {
                    cntK++; i++;
                }
                else if (a[i + 1] == 'H') {
                    cntKH++; i += 2;
                }
                else assert(0);
            }
            else { cntK++; i++; }
        }
        else if (a[i] == 'H') {
            cntH++; i++;
        }
        else assert(0);
    }

    {
        int tmp = min(cntSK, r);
        r -= tmp;
        cntSKH += tmp;
    }
    {
        int tmp = min(cntSH, q);
        q -= tmp;
        cntSKH += tmp;
    }
    {
        int tmp = min(cntKH, p);
        p -= tmp;
        cntSKH += tmp;
    }

    int ans2 = 0;
    while (cntS > 0 && cntK > 0 && cntH > 0 && p > 0 && q > 0 && r > 0) {
        if (min(q, r) > 0 && p <= q && p <= r && cntS > 0) {
            cntS--; q--; r--;
            ans2++;
        }
        else if (min(p, r) > 0 && q <= p && q <= r && cntK > 0) {
            cntK--; p--; r--;
            ans2++;
        }
        else if (min(p, q) > 0 && r <= p && r <= q && cntH > 0) {
            cntH--; p--; q--;
            ans2++;
        }
    }

    {
        int tmp = min({ cntS, q, r });
        q -= tmp; r -= tmp;
        ans2 += tmp;
    }
    {
        int tmp = min({ cntK, p, r });
        p -= tmp; r -= tmp;
        ans2 += tmp;
    }
    {
        int tmp = min({ cntH, p, q });
        p -= tmp; q -= tmp;
        ans2 += tmp;
    }

    ans2 += min({ p, q, r });

    cout << cntSKH + ans2;
}
