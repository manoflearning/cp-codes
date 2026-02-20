#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

ll query(char c) {
    cout << "? " << c << '\n';
    cout.flush();
    ll res; cin >> res;
    if(res == 0) exit(0);
    return res;
}

void qq(const string& s) {
    for(auto &c:s) {
        query(c);
    }
}

void right() {
    qq("FRRRLRRR");
}

void left() {
    qq("FLLLRLLL");
}

void straight4() {
    qq("RRRRLLLL");
}

void right3() {
    qq("FLLFLL");
}

void straight1() {
    straight4();
    right();
    right3();
    left();
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    ll ad = query('F');
    ll bd = query('F');

    if(ad < bd) {
        right(); right();
    }

    ll v = 3;
    ll ld = bd;

    ll xdis;
    bool xf = 0;

    while(1) {
        auto now = query('F');

        if(ld - now < v) {
            xf = 1;
            xdis = (ld - now + v) / 2;
        }

        ld = now;
        v++;

        if(xf) break;
    }

    ll ydis;
    bool yf = 0;

    left();

    ad = query('F');
    bd = query('F');

    if(ad < bd) {
        right(), right();
        xdis = -xdis;
    }

    while(1) {
        auto now = query('F');

        if(ld - now < v) {
            yf = 1;
            ydis = (ld - now + v) / 2;
        }

        ld = now;
        v++;

        if(yf) break;
    }

    right();
    
    while(xdis < 0) straight4(), xdis += 4;

    right();

    while(ydis > 4) straight4(), ydis -= 4;

    right();

    while(xdis > 4) straight4(), xdis -= 4;

    right();

    left();
    while(xdis) straight1(), xdis--;
    left();
    while(ydis) straight1(), ydis--;
}
