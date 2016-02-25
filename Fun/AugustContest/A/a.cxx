#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int p[16], counter=0;

void add(int a) {
	for (int i=0;i<16;++i) {
		p[i]+=a%2;
		a/=2;
	}
	++counter;
}

void del(int a) {
	for (int i=0;i<16;++i) {
		p[i]-=a%2;
		a/=2;
	}
	--counter;
}

int cnt(int a) {
	if (!a) {
		return counter;
	}
	int result=200000;
	for (int i=0;i<16;++i) {
		if (a%2) {
			result=min(result, p[i]);
		}
		a/=2;
	}
	return result;
}
int main(int argc, char **argv)
{
	int a,q;
	string s;
	cin >> q;
	
	for (int i=0;i<q;++i) {
		cin >> s >> a;
		switch (s[0]) {
			case 'a':
				add(a);
				break;
			case 'd':
				del(a);
				break;
			case 'c':
				cout << cnt(a) << endl;
				break;
		}
	}
	return 0;
}

