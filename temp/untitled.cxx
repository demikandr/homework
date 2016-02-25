/*
 * untitled.cxx
 * 
 * Copyright 2015 Unknown <demikandr@demikandr-laptop>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <vector>
#include <iostream>
#include <stdio.h>

//~ SuffArray::SuffArray(std::string source):p(source.length()), cnt(alphabet) {
	//~ std::vector < int > c(source.length());
	//~ for (size_t i = 0; i < source.length(); ++i) {
		//~ ++cnt[source[i]];
	//~ }
	//~ for (size_t i = 1; i < alphabet; ++i) {
		//~ cnt[i] += cnt[i-1];
	//~ }
	//~ for (size_t i = 0; i < source.length(); ++i) {
		//~ p[--cnt[source[i]]] = i;
	//~ }
	//~ c[p[0]] = 0;
	//~ int classes = 1;
	//~ for (size_t i = 1; i < source.length(); ++i) {
		//~ if (source[p[i]] != source[p[i - 1]]) {
			//~ ++classes;	
		//~ }
		//~ c[p[i]] = classes-1;
	//~ }
	//~ SuffArray::c.push_back(c);
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << i << '\t';
	//~ }
	//~ std::cout << std::endl;	
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << c[i] << '\t';
	//~ }
	//~ std::cout << std::endl;
	//~ std::vector < int > pn(source.length()), cn(source.length());
	//~ for (size_t h = 1; (size_t) (1 << h) < source.length(); ++h) {
		//~ for (size_t i = 0; i < source.length(); ++i) {
			//~ pn[i]=p[i] - (1 << h);
			//~ if (pn[i] < 0) {
				//~ pn[i] += source.length();
			//~ }
		//~ }
		//~ cnt.resize(classes);
		//~ std::fill(cnt.begin(), cnt.end(), 0);
		//~ for (size_t i = 0; i < source.length(); ++i) {
			//~ ++cnt[c[pn[i]]];
		//~ }
		//~ for (int i = 0; i < classes; ++i) {
			//~ cnt[i] += cnt[i-1];
		//~ }
		//~ for (int i = source.length()-1; i >= 0; --i) {
			//~ p[--cnt[c[pn[i]]]] = pn[i];
		//~ }
		//~ cn[p[0]] = 0;
		//~ classes = 1;
		//~ for (size_t i = 1; i < source.length(); ++i) {
			//~ int mid1 = (p[i] + (1 << h)) % source.length();
			//~ int mid2 = (p[i-1] + (1 << h)) % source.length();
			//~ if ((c[p[i]] != c[p[i - 1]]) || (c[mid1]!=c[mid2])) {
				//~ ++classes;
			//~ }
			//~ cn[p[i]]=classes-1;
		//~ }
		//~ c=cn;
		//~ SuffArray::c.push_back(c);
		//~ for (size_t i = 0; i < p.size(); ++i) {
			//~ std::cout << c[i] << '\t';
		//~ }
		//~ std::cout << std::endl;
	//~ }
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << p[i] << '\t';
	//~ }
	//~ std::cout << std::endl;
//~ }

class SuffArray {
	private:
		const unsigned int alphabet=100;
		std::vector <int> cnt, p;
		std::vector < std::vector < int > > c;
		
	public:
		SuffArray(std::string source);
		int comp(int l1, int r1, int l2, int r2);
};

SuffArray::SuffArray(std::string source):p(source.length()), cnt(alphabet) {
	std::vector < int > c(source.length());
	for (size_t i = 0; i < source.length(); ++i) {
		++cnt[source[i]];
	}
	for (size_t i = 1; i < alphabet; ++i) {
		cnt[i] += cnt[i-1];
	}
	for (size_t i = 0; i < source.length(); ++i) {
		p[--cnt[source[i]]] = i;
	}
	c[p[0]] = 0;
	int classes = 1;
	for (size_t i = 1; i < source.length(); ++i) {
		if (source[p[i]] != source[p[i - 1]]) {
			++classes;	
		}
		c[p[i]] = classes-1;
	}
	SuffArray::c.push_back(c);
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << i << '\t';
	//~ }
	//~ std::cout << std::endl;	
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << c[i] << '\t';
	//~ }
	//~ std::cout << std::endl;
	std::vector < int > pn(source.length()), cn(source.length());
	for (size_t h = 0; (size_t) (1 << h) < source.length(); ++h) {
		for (size_t i = 0; i < source.length(); ++i) {
			pn[i]=p[i] - (1 << h);
			if (pn[i] < 0) {
				pn[i] += source.length();
			}
		}
		cnt.resize(classes);
		std::fill(cnt.begin(), cnt.end(), 0);
		for (size_t i = 0; i < source.length(); ++i) {
			++cnt[SuffArray::c.back()[pn[i]]];
		}
		for (int i = 1; i < classes; ++i) {
			cnt[i] += cnt[i-1];
		}
		for (int i = source.length()-1; i >= 0; --i) {
			p[--cnt[SuffArray::c.back()[pn[i]]]] = pn[i];
		}
		cn[p[0]] = 0;
		classes = 1;
		for (size_t i = 1; i < source.length(); ++i) {
			int mid1 = (p[i] + (1 << h)) % source.length();
			int mid2 = (p[i-1] + (1 << h)) % source.length();
			if ((SuffArray::c.back()[p[i]] != SuffArray::c.back()[p[i - 1]]) || (SuffArray::c.back()[mid1]!=SuffArray::c.back()[mid2])) {
				++classes;
			}
			cn[p[i]]=classes-1;
		}
		SuffArray::c.push_back(cn);
		//~ for (size_t i = 0; i < p.size(); ++i) {
			//~ std::cout << c[i] << '\t';
		//~ }
		//~ std::cout << std::endl;
	}
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << p[i] << '\t';
	//~ }
	//~ std::cout << std::endl;
}

//~ SuffArray::SuffArray(std::string source):p(source.length()), cnt(alphabet) {
	//~ std::vector < int > c(source.length());
	//~ for (size_t i = 0; i < source.length(); ++i) {
		//~ ++cnt[source[i]];
	//~ }
	//~ for (size_t i = 1; i < alphabet; ++i) {
		//~ cnt[i] += cnt[i-1];
	//~ }
	//~ for (size_t i = 0; i < source.length(); ++i) {
		//~ p[--cnt[source[i]]] = i;
	//~ }
	//~ c[p[0]] = 0;
	//~ int classes = 1;
	//~ for (size_t i = 1; i < source.length(); ++i) {
		//~ if (source[p[i]] != source[p[i - 1]]) {
			//~ ++classes;	
		//~ }
		//~ c[p[i]] = classes-1;
	//~ }
	//~ SuffArray::c.push_back(c);
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << i << '\t';
	//~ }
	//~ std::cout << std::endl;	
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << c[i] << '\t';
	//~ }
	//~ std::cout << std::endl;
	//~ std::vector < int > pn(source.length()), cn(source.length());
	//~ for (size_t h = 1; (size_t) (1 << h) < source.length(); ++h) {
		//~ for (size_t i = 0; i < source.length(); ++i) {
			//~ pn[i]=p[i] - (1 << h);
			//~ if (pn[i] < 0) {
				//~ pn[i] += source.length();
			//~ }
		//~ }
		//~ cnt.resize(classes);
		//~ std::fill(cnt.begin(), cnt.end(), 0);
		//~ for (size_t i = 0; i < source.length(); ++i) {
			//~ ++cnt[c[pn[i]]];
		//~ }
		//~ for (int i = 1; i < classes; ++i) {
			//~ cnt[i] += cnt[i-1];
		//~ }
		//~ for (int i = source.length()-1; i >= 0; --i) {
			//~ p[--cnt[c[pn[i]]]] = pn[i];
		//~ }
		//~ cn[p[source.length()-1]] = 0;
		//~ classes = 1;
		//~ std::cout << "fuck" << std::endl;
		//~ for (int i = source.length()-2; i >= 0; --i) {
			//~ int mid1 = (p[i+1] + (1 << h)) % source.length();
			//~ int mid2 = (p[i] + (1 << h)) % source.length();
			//~ if ((c[p[i]] != c[p[i +1]]) || (c[mid1]!=c[mid2])) {
				//~ ++classes;
			//~ }
			//~ cn[p[i]]=classes-1;
		//~ }
		//~ std::cout << "fuck" << std::endl;
		//~ c=cn;
		//~ SuffArray::c.push_back(c);
		//~ for (size_t i = 0; i < p.size(); ++i) {
			//~ std::cout << c[i] << '\t';
		//~ }
		//~ std::cout << std::endl;
	//~ }
	//~ for (size_t i = 0; i < p.size(); ++i) {
		//~ std::cout << p[i] << '\t';
	//~ }
	//~ std::cout << std::endl;
//~ }

int SuffArray::comp(int l1, int r1, int l2, int r2) {
	
	int i = l1;
	int j = l2;
	int l = std::min(r1 - l1, r2 - l2);
	int k=0, t=1;
	while (t * 2 <= l) {
		t=t << 1;
		++k;
	}
	std::pair<int,int> a = std::make_pair (c[k][i], c[k][i+l-t]);
	std::pair<int,int> b = std::make_pair (c[k][j], c[k][j+l-t]);
	return ((a == b) ? ((r1-l1==r2-l2) ? 0 : ((r1-l1<r2-l2) ? -1 : 1 )): ((a < b) ? -1 : 1));
	return 0;
}

		


int main(int argc, char **argv)
{
	std::string string;
	std::cin >> string;
	for (size_t i = 0; i < string.length(); ++i) {
		string[i]-='a';
	}
	SuffArray sa(string);
	int l1, r1, l2, r2, m;
	std::cin  >> m;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		r1++, r2++;
		printf("%d\n", sa.comp(l1, r1, l2, r2));
	}
	return 0;
}

