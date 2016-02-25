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
	char *s; // входная строка
int n; // длина строки
 
// константы
const int maxlen = 2000000; // максимальная длина строки
const int alphabet = 256; // размер алфавита, <= maxlen
int p[maxlen], cnt[maxlen], c[maxlen];
memset (cnt, 0, alphabet * sizeof(int));
for (int i=0; i<n; ++i)
	++cnt[s[i]];
for (int i=1; i<alphabet; ++i)
	cnt[i] += cnt[i-1];
for (int i=0; i<n; ++i)
	p[--cnt[s[i]]] = i;
c[p[0]] = 0;
int classes = 1;
for (int i=1; i<n; ++i) {
	if (s[p[i]] != s[p[i-1]])  ++classes;
	c[p[i]] = classes-1;
}
int pn[maxlen], cn[maxlen];
for (int h=0; (1<<h)<n; ++h) {
	for (int i=0; i<n; ++i) {
		pn[i] = p[i] - (1<<h);
		if (pn[i] < 0)  pn[i] += n;
	}
	memset (cnt, 0, classes * sizeof(int));
	for (int i=0; i<n; ++i)
		++cnt[c[pn[i]]];
	for (int i=1; i<classes; ++i)
		cnt[i] += cnt[i-1];
	for (int i=n-1; i>=0; --i)
		p[--cnt[c[pn[i]]]] = pn[i];
	cn[p[0]] = 0;
	classes = 1;
	for (int i=1; i<n; ++i) {
		int mid1 = (p[i] + (1<<h)) % n,  mid2 = (p[i-1] + (1<<h)) % n;
		if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2])
			++classes;
		cn[p[i]] = classes-1;
	}
	memcpy (c, cn, n * sizeof(int));
}
    return 0;
}
