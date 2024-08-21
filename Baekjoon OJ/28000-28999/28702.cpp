#include <bits/stdc++.h>
using namespace std;

vector<string> s(3);

bool is_num(const string& t) {
    return t[0] != 'F' && t[0] != 'B';
}

void print(int x) {
    if (x % 3 == 0 && x % 5 == 0) cout << "FizzBuzz";
    if (x % 3 == 0 && x % 5 != 0) cout << "Fizz";
    if (x % 3 != 0 && x % 5 == 0) cout << "Buzz";
    if (x % 3 != 0 && x % 5 != 0) cout << x;
    exit(0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> s[0] >> s[1] >> s[2];

    if (is_num(s[0])) {
        print(stoi(s[0]) + 3);
    }
    else if (is_num(s[1])) {
        print(stoi(s[1]) + 2);
    }
    else if (is_num(s[2])) {
        print(stoi(s[2]) + 1);
    }
    else {
        for (int st = 1; ; st++) {
            bool is_valid = 1;
            for (int i = 0; i < 3; i++) {
                int x = st + i;
                is_valid &= (x % 3 == 0 && x % 5 == 0) == (s[i] == "FizzBuzz");
                is_valid &= (x % 3 == 0 && x % 5 != 0) == (s[i] == "Fizz");
                is_valid &= (x % 3 != 0 && x % 5 == 0) == (s[i] == "Buzz");
                is_valid &= (x % 3 != 0 && x % 5 != 0) == is_num(s[i]);
            }
            if (is_valid) {
                print(st + 3);
            }
        }
    }
}
