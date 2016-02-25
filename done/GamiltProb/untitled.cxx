#include <random>
#include <iostream>
#include <stdlib.h>

typedef std::mt19937 RNG;

std::uniform_int_distribution<uint32_t> ubool_dist(0, 1);

RNG rng;

const int MAXN=21, MAXPOWER2_N=3000000;

int COUNT_OF_TESTS=100;

bool gr[MAXN][MAXN], p[MAXPOWER2_N][MAXN], subset[MAXN];;

int power[21]{1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072, 262144, 524288, 1048576}, power2_n;

void makeRandomGraph(int countOfVertices) {
	for (int i=0;i<countOfVertices;++i) {
		for (int j=0;j<countOfVertices;++j) {
			gr[i][j]=gr[j][i]=(ubool_dist(rng)==1);
		}
	}
}

void getSet(int sizeOfSet,int codeOfSet, bool set[]) {  
	for (int i=0;i<sizeOfSet;++i) {
		//std::cout << codeOfSet%2 << ' ';
		set[i]=(codeOfSet%2==1);
		codeOfSet/=2;
	}
	//std::cout << std::endl;
}
	
void update(bool subset[], int r, int n, int codeOfSet) {
	for (int i=0;i<n;++i) {
		if ((subset[i])&&(p[codeOfSet-power[r]][i])&&(gr[i][r]==1)) {
			p[codeOfSet][r]=true;
			return;
		}
	}
}

bool hasGCycle(int n) {
	
	for (int i=0;i<power2_n;++i) {
		getSet(n,i, subset);
		for (int r=0;r<n;++r) {
			p[i][r]=(((i==1)&&(r==0))?true:false);
			if (subset[r]) {
				update(subset,r, n, i);
			}
		}
	}
	for (int i=1;i<n;++i) {
		if (p[power2_n-1][i]&&(gr[0][i])) {
			return true;
		}
	}
	return false;
}

double probabilityFor(int n) {
	int result=0;
	for (int i=0;i<COUNT_OF_TESTS;++i) {
		makeRandomGraph(n);
		if (hasGCycle(n)) {
			++result;
		}
	}
	return ((double)result)/((double) COUNT_OF_TESTS);
}
int main(int argc, char **argv)
{
	if (argc==4) {
		rng.seed(atoi(argv[2]));
	}
	else {
		rng.seed(100);
	}
	int n;
	n=std::atoi(argv[1]);
	power2_n=power[n];
	//std::cout << power2_n << ' ' << power[6] << ' ';
	COUNT_OF_TESTS=((n<10)?10000:1000);
	std::cout << probabilityFor(n) << ", ";
	
	return 0;
}

