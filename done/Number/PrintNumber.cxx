#include <cmath>
#include <iostream>

const double EPS=5e-5;
const double INF=1000000000;

class Dot {
	public:
		Dot(const double x, const double y): x(x), y(y) {}
		Dot() {}
		double x;
		double y;
};

double getDistance(const Dot& a, const Dot& b) {
	return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}

typedef std::pair< double, std::pair<std::pair <int, int>, std::pair<int, int> > > WTFType;

WTFType p[5001][5001], result;
void print(WTFType& a) {
	if ((a.second.second.first!=0)||(a.second.second.second!=0)) {
		print(p[a.second.second.first][a.second.second.second]);
	}
	std::cout << ((a.second.first.first>a.second.first.second)?'L':'R');
}

int main(int argc, char **argv)
{
	int m, n, l;
	std::cin >> m >> n >> l;
	Dot digits[l+1];
	Dot leftHandBegin(0,0), rightHandBegin(n-1, 0);
	for (int i=1;i<=l;++i) {
		std::cin >> digits[i].x >> digits[i].y;
	}
	
	for (int i=0;i<=l;++i) {
		for (int j=0;j<=l;++j) {
			if ((i==0) && (j==0)) {
				p[i][j].first=0;
				p[i][j].second.first.first=p[i][j].second.first.second=p[i][j].second.second.first=p[i][j].second.second.second=0;
			}
			else if (i==0) {
				p[i][j]=p[i][j-1];
				p[i][j].first+=getDistance(digits[j], ((j-1==0)? rightHandBegin:digits[j-1]));
			}
			else if (j==0) {
				p[i][j]=p[i-1][j];
				p[i][j].first+=getDistance(digits[i], ((i-1==0)? leftHandBegin:digits[i-1]));
			}
			else if (i==j) {
				p[i][j]=p[0][0];
				p[i][j].first=INF;
			}
			else if (fabs(i-j)>1) {
				if (i>j) {
					p[i][j]=p[i-1][j];
					p[i][j].first+=getDistance(digits[i], digits[i-1]);
				}
				else {
					p[i][j]=p[i][j-1];
					p[i][j].first+=getDistance(digits[j], digits[j-1]);
				}
			}
			else if (i > j) {
				p[i][j]=p[0][j];
				p[i][j].first+=getDistance(leftHandBegin, digits[i]);
				for (int q=0;q<j;++q) {
					p[i][j]=std::min(p[i][j], std::make_pair(p[q][j].first+getDistance(digits[q], digits[i]), p[q][j].second));
				}
			}
			else {
				p[i][j]=p[i][0];
				p[i][j].first+=getDistance(rightHandBegin, digits[j]);
				for (int q=1;q<i;++q) {
					p[i][j]=std::min(p[i][j], std::make_pair(p[i][q].first+getDistance(digits[j], digits[q]),p[i][q].second));
				}
			}
			p[i][j].second.second.first=p[i][j].second.first.first, p[i][j].second.second.second=p[i][j].second.first.second, p[i][j].second.first.first=i, p[i][j].second.first.second=j;
			//std::cout << p[i][j].second.second.first << ' '<< p[i][j].second.second.second << ' ' << p[i][j].first << " * ";
		}
		//std::cout << std::endl;
	}
	result=p[1][1];
	for (int i=0;i<l;++i) {
		result=std::min(result, std::min(p[i][l],p[l][i]));
	}
	//std::cout << result.second.first.first << ' '<< result.second.first.second << ' ' << result.first << " * ";
	print(result);
	return 0;
}

