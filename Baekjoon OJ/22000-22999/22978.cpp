#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n;
string s;
vector<pair<int, int>> Write;

int trans(string x) {
    int ret = 0;
    for (int i = 0; i < sz(x); i++) {
        if (x[i] == '1') ret |= (1 << i);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    
    for (int i = 0; i < 512; i++) {
        Write.push_back({ i, i / 2 });
    }

    for (int i = 0, k = 0; i < sz(s); i += 9, k++) {
        int x = 0;
        for (int j = i; j < min(i + 9, sz(s)); j++)
            if (s[j] == '1') x |= (1 << (j - i));
        Write.push_back({ 512 + k, x });
    }

    Write.push_back({ 200'000, 512 });

    // print
    cout << sz(Write) + 12 << '\n';
    for (auto& i : Write)
        cout << "Write " << i.first << ' ' << i.second << '\n';

    cout << "Start\n";
    cout << "Print **200000\n";
    cout << "Print ***200000\n";
    cout << "Print ****200000\n";
    cout << "Print *****200000\n";
    cout << "Print ******200000\n";
    cout << "Print *******200000\n";
    cout << "Print ********200000\n";
    cout << "Print *********200000\n";
    cout << "Print **********200000\n";
    cout << "Add 200000\n";
    cout << "End\n";
}