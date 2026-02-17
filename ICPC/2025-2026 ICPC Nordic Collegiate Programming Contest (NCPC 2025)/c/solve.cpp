#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    string st1, st2, en1, en2;
    cin >> st1 >> st2 >> en1 >> en2;


    auto get_day = [](const string &s) -> int {
        if (s == "Mon") return 0;
        else if (s == "Tue") return 1;
        else if (s == "Wed") return 2;
        else if (s == "Thu") return 3;
        else if (s == "Fri") return 4;
        else if (s == "Sat") return 5;
        else if (s == "Sun") return 6;
        else return -1;
    };

    auto get_minute = [](const string &s) -> int {
        int ret = 0;
        ret += 10 * 60 * (s[0] - '0');
        ret += 60 * (s[1] - '0');
        ret += 10 * (s[3] - '0');
        ret += (s[4] - '0');
        return ret;
    };

    int st_d = get_day(st1);
    int en_d = get_day(en1);

    int st_m = get_minute(st2);
    int en_m = get_minute(en2);

    if (st_d > en_d) {
        en_d += 7;
    } else if (st_d == en_d && st_m >= en_m) {
        en_d += 7;
    }

    int sum = 0;
    sum += 24 * 60 * (en_d - st_d);
    sum += en_m - st_m;

    int d = sum / (24 * 60);
    int h = sum % (24 * 60) / 60;
    int m = sum % 60;

    auto print = [](int x, string unit, bool comma) {
        cout << x << ' ' << unit << (x > 1 ? "s" : "") << (comma ? ", " : " ");
    };

    if ((int)(d > 0) + (h > 0) + (m > 0) == 3) {
        print(d, "day", 1);
        print(h, "hour", 1);
        print(m, "minute", 0);
    } else if ((int)(d > 0) + (h > 0) + (m > 0) == 2) {
        if (d > 0 && h > 0) {
            print(d, "day", 0);
            cout << "and ";
            print(h, "hour", 0);
        } else if (d > 0 && m > 0) {
            print(d, "day", 0);
            cout << "and ";
            print(m, "minute", 0);
        } else if (h > 0 && m > 0) {
            print(h, "hour", 0);
            cout << "and ";
            print(m, "minute", 0);
        }
    } else if ((int)(d > 0) + (h > 0) + (m > 0) == 1) {
        if (d > 0) print(d, "day", 0);
        else if (h > 0) print(h, "hour", 0);
        else if (m > 0) print(m, "minute", 0);
    }
}
