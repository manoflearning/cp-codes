#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

typedef complex<double> base;

void fft(vector<base> &a, bool inv){
	int n = a.size(), j = 0;
	vector<base> roots(n / 2);
	for (int i = 1; i < n; i++){
		int bit = (n >> 1);
		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++){
		roots[i] = base(cos(ang * i), sin(ang * i));
	}
	for (int i = 2; i <= n; i <<= 1){
		int step = n / i;
		for (int j = 0; j < n; j += i){
			for (int k = 0; k < i / 2; k++) {
				base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (inv) for (int i = 0; i < n; i++) a[i] /= n; // skip for OR convolution.
}

vector<ll> multiply(const vector<ll>& v, const vector<ll>& w) {
	vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
	int n = 2; while (n < v.size() + w.size()) n <<= 1;
	fv.resize(n); fw.resize(n);
	fft(fv, 0); fft(fw, 0);
	for (int i = 0; i < n; i++) fv[i] *= fw[i];
	fft(fv, 1);
	vector<ll> ret(n);
	for (int i = 0; i < n; i++) ret[i] = (ll)round(fv[i].real());
	return ret;
}

const int MAXN = 1000000;

bool isPrime[MAXN + 1];
vector<int> prime;

void getPrime() {
	fill(isPrime + 2, isPrime + MAXN + 1, 1);

	for (ll i = 4; i <= MAXN; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAXN; i++) {
		if (isPrime[i]) prime.push_back(i);
		for (ll j = i * i; j <= MAXN; j += i * 2)
			isPrime[j] = 0;
	}
}

const int MAXC = 500001;

vector<ll> p(MAXC), p2(MAXC);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

	getPrime();

    for (auto& i : prime) {
        p[i / 2] = 1;
        if (i - 1 < MAXC) p2[i - 1] = 1;
    }

    vector<ll> a = multiply(p, p);
    a.resize(MAXC);
    vector<ll> b = multiply(a, p);
    b.resize(MAXC);
    vector<ll> c = multiply(p, p2);
    c.resize(MAXC);

    for (int i = 0; i < MAXC; i++) {
        int isMul3 = ((i * 2 + 3) % 3 == 0);

        if (isMul3) c[i]--;

        b[i] -= 3 * c[i] + isMul3;
        b[i] /= 6;
    }

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        cout << b[(n - 3) / 2] + c[(n - 3) / 2] + isPrime[n - 4] + (n % 3 == 0) << '\n';
    }

	return 0;
}