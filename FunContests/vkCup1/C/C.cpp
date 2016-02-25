#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef long long li;
typedef unsigned long long uli;
typedef long double ld;

const int INF = 1e9;
const li lINF = 1e18;
const int P = 1e9 + 7, Q = 1e9 + 9;
const int base = 41;
const double PI = 3.141592653589793238;
const double eps = 1e-7;

#ifdef DEBUG
#define dout(x) cerr << x
#else
#define dout(x)
#endif // DEBUG

inline bool is_letter (char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

inline bool is_digit (char c)
{
    return '0' <= c && c <= '9';
}

vector <pair <int, int> > a(100001);
int main()
{
#ifdef DEBUG
    freopen ("test.in", "r", stdin);
#endif // DEBUG
	int n,k,q, x,l,r;
	cin >> n >> k;
	for (int i=0;i<n;++i) {
		scanf("%d",&a[i].fi);
		a[i].se=1;
	}
	for (int i=0;i<n;++i) {
		for (int j=1;j<k;j++) {
			a[j*n+i].fi=a[i].fi*(j+1);
			a[j*n+i].se=j+1;
		}
	}
	a[n*k].fi=0;
	a[n*k].se=0;
	sort(a.begin(), a.begin()+n*k+1);
	for (int i=1;i<n*k;++i) {
		if (a[i].fi==a[i-1].fi) {
			a[i].se=min(a[i].se, a[i-1].se);
		}
	}
	for (int i=n*k-2;i>=0;--i) {
		if (a[i].fi==a[i+1].fi) {
			a[i].se=min(a[i].se, a[i+1].se);
		}
	}
	cin >> q;
	for (int p=0;p<q; ++p) {
		cin >> x;
		l=0;
		r=k*n;
		int mink=k+1;
		while (l<=r) {
			if (a[r].fi+a[l].fi<x) {
				++l;
			}
			else
			if (a[r].fi+a[l].fi>x) {
				--r;
			}
			else {
				mink=min(mink, a[r].se+a[l].se);
				--r, ++l;
			}
		}
		if (mink==k+1) {
			cout << -1 << endl;
		}
		else
			cout << mink << endl;
	}
    return 0;
}
