// 0 <= Ai <= N for all i
// sum(Ai) = N
// A0 != 0

// N = 1 -> 없음
// N = 2 -> 없음
// N = 3 -> 없음
// N = 4 -> (2 0 2 0), (1 2 1 0)
// N = 5 -> (2 1 2 0 0)
// N = 6 -> 없음
// N = 7 -> (3 2 1 1 0 0 0)
// N = 8 -> (4 2 1 0 1 0 0 0)
// N = 9 -> (5 2 1 0 0 1 0 0 0)
// N = 10 -> (6 2 1 0 0 0 1 0 0 0)
// N = 11 -> (7 2 1 0 0 0 0 1 0 0 0)
// N = 12 -> (8 2 1 0 0 0 0 0 1 0 0 0)
// N = 13 -> (9 2 1 0 0 0 0 0 0 1 0 0 0)
// N = 14 -> (10 2 1 0 0 0 0 0 0 0 1 0 0 0)
// N = 15 -> (11 2 1 0 0 0 0 0 0 0 0 1 0 0 0)
// N = 16 -> (12 2 1 0 0 0 0 0 0 0 0 0 1 0 0 0)

#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int N; cin >> N;
        if (N == 1 || N == 2 || N == 3 || N == 6) {
            cout << 0 << '\n';
            continue;
        }
        if (N == 4) {
            cout << 2 << '\n';
            continue;
        }
        cout << 1 << '\n';
    }
}

// naive bruteforce
/*#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> A;
int sum = 0;
int cnt[101];
int ans = 0;

void bt(int idx) {
    if (sum > N) return;

    if (idx == N) {
        if (sum != N) return;
        for (int i = 0; i < N; i++) {
            if (A[i] != cnt[i]) return;
        }

        ans++;
        for (auto& i : A)
            cout << i << ' ';
        cout << '\n';
        
        return;
    }

    for (int i = (idx == 0 ? 1 : 0); i <= min(N, N - sum); i++) {
        A.push_back(i);
        cnt[i]++;
        sum += i;
        
        bt(idx + 1);
        
        A.pop_back();
        cnt[i]--;
        sum -= i;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    N = 16;

    bt(0);
    cout << ans;
}*/