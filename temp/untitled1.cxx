#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
#include <stdio.h>

long long int qq=71;
long long int p=1000000009;
std::vector <long long int> hash, q;
bool eqHash(int l1, int l2, int length) {
	return ((hash[l1+length]+p*p-hash[l1]*q[length])%p==(hash[l2+length]+p*p-hash[l2]*q[length])%p);
}

int main(int argc, char **argv){
	std::string string;
	
	std::cin >> string;
	hash.push_back(0);
	hash.push_back(string[0]-'A');
	q.push_back(1);
	for (int i=1;i<(int) string.length();++i) {
		hash.push_back((hash.back()*qq+(string[i]-'A'))%p);
		q.push_back((q.back()* qq)%p);
	}
	int l1, r1, l2, r2, l, r, m;
	std::cin >> m;
	for (int i=0; i<m;++i) {
		scanf("%d%d%d%d", &l1, &r1, &l2,&r2);
		r1++, r2++;
		int t=std::min(r1-l1, r2-l2);
		l=0, r=t;
		while (l<r) {
			int mid=(l+r)/2+(l+r)%2;
			if (!eqHash(l1,l2,mid)) {
				r=mid-1;
			}
			else {
				l=mid;
			}
		}
		int out=0;
		if (r==t) {
			if (r1-l1<r2-l2) {
				out=-1;
			}
			if (r1-l1>r2-l2) {
				out=1;
			}
		}
		else
		if (string[l1+r]>string[l2+r]) {
			out=1;
		}
		else
			out=-1;
		printf("%d\n",out);
	}
			
		
	return 0;
}
