#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;



int main(int argc, char **argv)
{
	ios_base::sync_with_stdio(false);
	int n, result=0;
	cin >> n;
	vector<int> p(n);
	for (int i=0;i<n;++i) {
		cin >> p[i];
	}
	map<int, int> m;
	for (int i=n-1;i>=0;--i) {
		while ((!m.empty()) && (m.begin()->first < p[i])) {
			result=max(result, m.begin()->second - i);
			m.erase(m.begin());
		}
		m[p[i]]=i;
	}
	cout << result;
		
		
	
	return 0;
}

