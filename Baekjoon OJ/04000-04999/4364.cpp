#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll w, h, l, H;

bool tilt_forward(ll x, ll y, ll z) {
    double cos_theta = (double)x / H;
    double sin_theta = sqrt(1 - cos_theta * cos_theta);

    bool ret = 1;
    ret &= (H >= x);
    ret &= (l + 1e-6 >= y * cos_theta + x * sin_theta);
    ret &= (h + 1e-6 >= y * sin_theta + x * cos_theta);
    ret &= (w >= z);
    return ret;
}

bool tilt_sideways(ll x, ll y, ll z) {
    bool ret = 1;
    ret &= (H < x);
    ret &= (w < z);
    ret &= (l >= y);
    ret &= ((H + w) * (H + w) >= z * z + x * x + x * z);
    return ret;
}

void yes() { cout << "The box goes on the truck.\n"; }
void no() { cout << "The box will not go on the truck.\n"; }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        cin >> w;
        if (cin.eof()) break;
        cin >> h >> l >> H;
        ll x, y, z;
        cin >> x >> y >> z;

        bool ans = 0;
        ans |= tilt_forward(x, y, z) | tilt_sideways(x, y, z);
        ans |= tilt_forward(x, z, y) | tilt_sideways(x, z, y);
        ans |= tilt_forward(y, x, z) | tilt_sideways(y, x, z);
        ans |= tilt_forward(y, z, x) | tilt_sideways(y, z, x);
        ans |= tilt_forward(z, x, y) | tilt_sideways(z, x, y);
        ans |= tilt_forward(z, y, x) | tilt_sideways(z, y, x);

        ans ? yes() : no();
    }
}
