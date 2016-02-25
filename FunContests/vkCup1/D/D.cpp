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



const int MAXN=4000000;

int a[MAXN], b[MAXN];
int buildTree(int begin ,int end, int pos) {
	if (end-begin==1) {
		a[pos]=b[begin];
		return a[pos];
	}
	int mid=begin+(end-begin)/2;
	a[pos]=min(buildTree(begin, mid, pos*2+1), buildTree(mid, end, pos*2+2));
	return a[pos];
}
int minB(int begin, int end, int begins, int ends, int pos) {
	if ((begins<=begin)&&(end<=ends)) {
		return a[pos];
	}
	if ((ends<=begin)||(end<=begins)) {
		return INF;
	}
	int mid=begin+(end-begin)/2;
	return min(minB(begin, mid, begins, ends, pos*2+1), minB(mid, end, begins, ends, pos*2+2));
}

int main()
{
#ifdef DEBUG
    freopen ("test.in", "r", stdin);
#endif // DEBUG
    return 0;
}
