// if K = N / 2 => (((...)))
// if K = N - 1 => ()()...()
// if K = N - 2 => (())(())...(())
// if K = N - 3 => ((()))((()))...((()))
// if K = N => -1

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int N, K;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> K;

    if (K < N / 2) cout << -1;
    else if (K == N) cout << -1;
    else {
        int len = N - K;
        int cnt = N / 2;
        while (cnt >= len) {
            cnt -= len;
            for (int i = 0; i < len; i++) cout << '(';
            for (int i = 0; i < len; i++) cout << ')';
        }
        for (int i = 0; i < cnt; i++) cout << '(';
        for (int i = 0; i < cnt; i++) cout << ')';
    }
}