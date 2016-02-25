#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

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

int main()
{
#ifdef DEBUG
    freopen ("test.in", "r", stdin);
#endif // DEBUG
	
	int n;
	cin >> n;
	vector <pair <int, int> > m(n);
	int maxh=0, sumw=0, maxw=0;
	for (int i=0;i<n; ++i) {
		cin >> m[i].sc >> m[i].fs;
		if (m[i].fs<m[i].sc)
			swap(m[i].fs, m[i].sc);
		maxh=max(m[i].fs, maxh);
		sumw+=m[i].sc;
	}
	sort(m.begin(), m.end());
	int minp=maxh*sumw;
	
	for (int i=n-1; i>=0;--i) {
		maxw=max(maxw,m[i].sc);
		sumw=sumw-m[i].sc+m[i].fs;
		maxh=max((i>0) ? m[i-1].fs: 0, maxw);
		minp=min(minp, maxh*sumw);
	}
	cout << minp;
    return 0;
}
