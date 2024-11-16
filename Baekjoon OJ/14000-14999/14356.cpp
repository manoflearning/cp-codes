#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

struct Result {
    string sequence;
    int R, P, S;

    Result(string seq = "", int r = 0, int p = 0, int s = 0)
        : sequence(seq), R(r), P(p), S(s) {}
};

map<pair<int, char>, Result> memo;

bool compare(const Result &a, const Result &b) {
    return a.sequence < b.sequence;
}

Result generate_sequence(int N, char winner) {
    auto key = make_pair(N, winner);
    if (memo.count(key)) {
        return memo[key];
    }

    if (N == 0) {
        return Result(string(1, winner),
                      winner == 'R', winner == 'P', winner == 'S');
    }

    vector<Result> candidates;

    if (winner == 'R') {
        Result left = generate_sequence(N - 1, 'R');
        Result right = generate_sequence(N - 1, 'S');

        Result res1(left.sequence + right.sequence,
                    left.R + right.R, left.P + right.P, left.S + right.S);
        Result res2(right.sequence + left.sequence,
                    left.R + right.R, left.P + right.P, left.S + right.S);

        candidates.push_back(res1);
        candidates.push_back(res2);
    } else if (winner == 'P') {
        Result left = generate_sequence(N - 1, 'P');
        Result right = generate_sequence(N - 1, 'R');

        Result res1(left.sequence + right.sequence,
                    left.R + right.R, left.P + right.P, left.S + right.S);
        Result res2(right.sequence + left.sequence,
                    left.R + right.R, left.P + right.P, left.S + right.S);

        candidates.push_back(res1);
        candidates.push_back(res2);
    } else if (winner == 'S') {
        Result left = generate_sequence(N - 1, 'S');
        Result right = generate_sequence(N - 1, 'P');

        Result res1(left.sequence + right.sequence,
                    left.R + right.R, left.P + right.P, left.S + right.S);
        Result res2(right.sequence + left.sequence,
                    left.R + right.R, left.P + right.P, left.S + right.S);

        candidates.push_back(res1);
        candidates.push_back(res2);
    }

    sort(candidates.begin(), candidates.end(), compare);
    Result best = candidates[0];

    memo[key] = best;
    return best;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << ": ";

        int N, R, P, S;
        cin >> N >> R >> P >> S;

        int total_players = 1 << N;
        bool found = false;
        string answer = "IMPOSSIBLE";

        char moves[] = {'R', 'P', 'S'};
        for (char winner : moves) {
            memo.clear();
            Result res = generate_sequence(N, winner);    

            if (res.R == R && res.P == P && res.S == S) {
                if (!found || res.sequence < answer) {
                    answer = res.sequence;
                    found = true;
                }
            }
        }

        cout << answer << '\n';;
    }
}
