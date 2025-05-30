#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

typedef complex<double> cpx;
void fft(vector<cpx> &a, bool inv){
    int n = a.size(), j = 0;
    vector<cpx> roots(n/2);
    for(int i=1; i<n; i++){
        int bit = (n >> 1);
        while(j >= bit) j -= bit, bit >>= 1;
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }
    double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
    for(int i=0; i<n/2; i++) roots[i] = cpx(cos(ang * i), sin(ang * i));
    for(int i=2; i<=n; i<<=1){
        int step = n / i;
        for(int j=0; j<n; j+=i) for(int k=0; k<i/2; k++){
            cpx u = a[j+k], v = a[j+k+i/2] * roots[step * k];
            a[j+k] = u+v; a[j+k+i/2] = u-v;
        }
    }
    if(inv) for(int i=0; i<n; i++) a[i] /= n;
}
vector<ll> multiply(vector<ll> &v, vector<ll> &w){
    vector<cpx> fv(v.begin(), v.end()), fw(w.begin(), w.end());
    int n = 2; while(n < v.size() + w.size()) n <<= 1;
    fv.resize(n); fw.resize(n);
    fft(fv, 0); fft(fw, 0);
    for(int i=0; i<n; i++) fv[i] *= fw[i];
    fft(fv, 1);
    vector<ll> ret(n);
    for(int i=0; i<n; i++) ret[i] = (ll)round(fv[i].real());
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;

    vector<ll> a(n), b(n);
    for (ll i = 1; i < n; i++) {
        a[i * i % n]++;
        b[i * i % n]++;
    }

    vector<ll> c = multiply(a, b);
    for (ll i = n; i < sz(c); i++) {
        c[i % n] += c[i];
    }

    for (ll i = 0; i < n; i++) {
        c[2 * i % n] += a[i];
    }

    ll ans = 0;
    for (ll i = 1; i < n; i++) {
        ans += c[i * i % n] / 2;
    }
    cout << ans;
}
